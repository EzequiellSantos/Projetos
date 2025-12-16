#include "../includes/bomb.h"
#include "../includes/mapa.h"
#include "../includes/player.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// Variáveis globais
// Para contagem de obstáculos destruídos
static int obstaculos_destruidos_ultima_explosao = 0;
static int dono_ultima_explosao = 0;
static int proximo_id_bomba = 1;
Bomba bombas_ativas[50] = {0};
int total_bombas_ativas = 0;
Explosao explosoes_ativas[200] = {0};
int total_explosoes_ativas = 0;

// Configurações das bombas
ConfigBomba config_bombas[4] = {
    // BOMBA_INICIAL
    {
        .nome = "Peidivea",
        .dano = 10,
        .emoji = "⚪",
        .cor_explosao = COLOR_PAIR(4),  // Verde
        .raio = 5,
        .quantidade = -1,
        .formato = 0
    },
    // BOMBA_MEDIA
    {
        .nome = "Rasga-Lata",
        .dano = 30,
        .emoji = "🧨",
        .cor_explosao = COLOR_PAIR(3),
        .raio = 0 ,
        .quantidade = 10,
        .formato = 1
    },
    // BOMBA_FORTE
    {
        .nome = "Treme-Terra",
        .dano = 50,
        .emoji = "💣",
        .cor_explosao = COLOR_PAIR(1),
        .raio = 0,
        .quantidade = 10,
        .formato = 2
    },
    // BOMBA_NUKE
    {
        .nome = "LgK10",
        .dano = 90,
        .emoji = "📱",
        .cor_explosao = COLOR_PAIR(2),
        .raio = 0,
        .quantidade = 10,
        .formato = 3
    }
};

// Inicializar sistema de bombas
void inicializar_sistema_bombas() {
    total_bombas_ativas = 0;
    total_explosoes_ativas = 0;
    srand(time(NULL));
}

// Obter configuração da bomba
ConfigBomba obter_config_bomba(TipoBomba tipo) {
    return config_bombas[tipo];
}

// Gerar bomba surpresa aleatória
TipoBomba gerar_bomba_surpresa() {
    int r = rand() % 100;
    if (r < 60) {
        return BOMBA_MEDIA;     // 60% de chance
    } else if (r < 99) {
        return BOMBA_FORTE;     // 39% de chance
    } else {
        return BOMBA_NUKE;      // 1% de chance
    }
}

// Plantar uma bomba
void plantar_bomba(Player *jogador, int offset_x, int offset_y) {
    // Verificar se está em cooldown
    if (jogador->cooldown_bomba > 0) {
        return;
    }
    
    // Verificar se o jogador pode plantar
    if (jogador->bomba_atual != BOMBA_INICIAL && jogador->quantidade_bomba_atual <= 0) {
        return;
    }
    
    // Verificar se há espaço para mais bombas
    if (total_bombas_ativas >= 50) {
        return;
    }
    
    // Converter posição do jogador para coordenadas do mapa
    int mapa_x = jogador->x - offset_x;
    int mapa_y = jogador->y - offset_y;
    
    // Verificar se a posição é válida (não há bomba no local)
    for (int i = 0; i < total_bombas_ativas; i++) {
        if (bombas_ativas[i].ativa && 
            bombas_ativas[i].x == mapa_x && 
            bombas_ativas[i].y == mapa_y) {
            return;
        }
    }
    
    // Contar obstáculos ao redor para estimativa
    int obstaculos_ao_redor = 0;
    for (int dy = -2; dy <= 2; dy++) {
        for (int dx = -2; dx <= 2; dx++) {
            int nx = mapa_x + dx;
            int ny = mapa_y + dy;
            if (nx >= 0 && nx < MAX_W && ny >= 0 && ny < MAX_H) {
                if (mapa_colisao[ny][nx] == OBSTACULO_DESTRUTIVEL) {
                    obstaculos_ao_redor++;
                }
            }
        }
    }
    
    // Criar nova bomba
    bombas_ativas[total_bombas_ativas].id = proximo_id_bomba++;
    bombas_ativas[total_bombas_ativas].x = mapa_x;
    bombas_ativas[total_bombas_ativas].y = mapa_y;
    bombas_ativas[total_bombas_ativas].tipo = jogador->bomba_atual;
    bombas_ativas[total_bombas_ativas].timer = 90;
    bombas_ativas[total_bombas_ativas].ativa = true;
    bombas_ativas[total_bombas_ativas].explodindo = false;
    bombas_ativas[total_bombas_ativas].fase_explosao = 0;
    bombas_ativas[total_bombas_ativas].dono = jogador->dono;
    
    total_bombas_ativas++;
    jogador->bombas_jogadas++;
    
    // Adicionar estimativa de obstáculos que serão destruídos
    if (obstaculos_ao_redor > 0) {
        jogador->obstaculos_destruidos += obstaculos_ao_redor / 2; // Estimativa
    }
    
    // Definir cooldown de 60 frames (2 segundos a 30 FPS)
    jogador->cooldown_bomba = 60;
    
    // Decrementar quantidade se não for infinita
    if (jogador->bomba_atual != BOMBA_INICIAL) {
        jogador->quantidade_bomba_atual--;
        if (jogador->quantidade_bomba_atual == 0) {
            jogador->bomba_atual = BOMBA_INICIAL;
            jogador->quantidade_bomba_atual = -1;
        }
    }
}

// Atualizar estado das bombas
// Atualizar estado das bombas
void atualizar_bombas(int mapa_altura, int mapa_largura, Player *p1, Player *p2) {
    (void)mapa_altura;
    
    // Atualizar bombas
    for (int i = 0; i < total_bombas_ativas; i++) {
        if (bombas_ativas[i].ativa) {
            if (bombas_ativas[i].explodindo) {
                bombas_ativas[i].fase_explosao++;
                if (bombas_ativas[i].fase_explosao > 30) {
                    bombas_ativas[i].ativa = false;
                    
                    // ATUALIZAR OBSTÁCULOS DESTRUÍDOS AQUI
                    if (dono_ultima_explosao == 1) {
                        p1->obstaculos_destruidos += obstaculos_destruidos_ultima_explosao;
                    } else if (dono_ultima_explosao == 2) {
                        p2->obstaculos_destruidos += obstaculos_destruidos_ultima_explosao;
                    }
                    
                    // Resetar contadores
                    obstaculos_destruidos_ultima_explosao = 0;
                    dono_ultima_explosao = 0;
                    
                    // Remover bomba do array
                    for (int j = i; j < total_bombas_ativas - 1; j++) {
                        bombas_ativas[j] = bombas_ativas[j + 1];
                    }
                    total_bombas_ativas--;
                    i--;
                }
            } else {
                bombas_ativas[i].timer--;
                if (bombas_ativas[i].timer <= 0) {
                    bombas_ativas[i].explodindo = true;
                    bombas_ativas[i].fase_explosao = 0;
                    
                    // Iniciar explosão
                    ConfigBomba config = obter_config_bomba(bombas_ativas[i].tipo);
                    
                    // Calcular raio
                    int raio = config.raio;
                    if (raio == 0) {
                        if (config.formato == 3) {
                            raio = (mapa_largura * 3) / 4;
                        } else {
                            raio = mapa_largura / 2;
                        }
                    }
                    
                    // Criar explosões
                    destruir_obstaculos(bombas_ativas[i].x, bombas_ativas[i].y, 
                                    raio, config.formato, bombas_ativas[i].dono, 
                                    bombas_ativas[i].tipo, bombas_ativas[i].id);
                }
            }
        }
    }
    
    // Atualizar explosões
    for (int i = 0; i < total_explosoes_ativas; i++) {
        if (explosoes_ativas[i].ativa) {
            explosoes_ativas[i].timer--;
            if (explosoes_ativas[i].timer <= 0) {
                explosoes_ativas[i].ativa = false;
                
                // Remover explosão do array
                for (int j = i; j < total_explosoes_ativas - 1; j++) {
                    explosoes_ativas[j] = explosoes_ativas[j + 1];
                }
                total_explosoes_ativas--;
                i--;
            }
        }
    }
}
// Desenhar explosões
void desenhar_explosoes(int offset_x, int offset_y) {
    for (int i = 0; i < total_explosoes_ativas; i++) {
        if (explosoes_ativas[i].ativa) {
            attron(explosoes_ativas[i].cor);
            mvaddch(offset_y + explosoes_ativas[i].y, 
                   offset_x + explosoes_ativas[i].x, 
                   '*');
            attroff(explosoes_ativas[i].cor);
        }
    }
}

// Destruir obstáculos e criar explosões
// Destruir obstáculos e criar explosões - VERSÃO COMPLETA
void destruir_obstaculos(int x, int y, int raio, int formato, int dono, TipoBomba tipo_bomba, int id_bomba) {
    ConfigBomba config = obter_config_bomba(tipo_bomba);
    
    // Contador de obstáculos destruídos
    int obstaculos_destruidos = 0;
    
    // Vetores de direção baseados no formato
    int dir_x[8] = {0};
    int dir_y[8] = {0};
    int num_direcoes = 0;
    
    switch (formato) {
        case 0: // Disco
            for (int dy = -raio; dy <= raio; dy++) {
                for (int dx = -raio; dx <= raio; dx++) {
                    if (dx*dx + dy*dy <= raio*raio) {
                        int nx = x + dx;
                        int ny = y + dy;
                        
                        if (nx >= 0 && nx < MAX_W && ny >= 0 && ny < MAX_H) {
                            if (mapa_colisao[ny][nx] == OBSTACULO_DESTRUTIVEL) {
                                mapa_colisao[ny][nx] = LIVRE;
                                mapa_visual[ny][nx] = ' ';
                                obstaculos_destruidos++;
                            }
                            
                            // Adicionar explosão visual
                            if (total_explosoes_ativas < 200) {
                                explosoes_ativas[total_explosoes_ativas].id_bomba = id_bomba;
                                explosoes_ativas[total_explosoes_ativas].x = nx;
                                explosoes_ativas[total_explosoes_ativas].y = ny;
                                explosoes_ativas[total_explosoes_ativas].timer = 30;
                                explosoes_ativas[total_explosoes_ativas].cor = config.cor_explosao;
                                explosoes_ativas[total_explosoes_ativas].ativa = true;
                                explosoes_ativas[total_explosoes_ativas].tipo_bomba = tipo_bomba;
                                explosoes_ativas[total_explosoes_ativas].dono_explosao = dono;
                                explosoes_ativas[total_explosoes_ativas].dano = config.dano;
                                // INICIALIZAR CONTROLE DE DANO POR JOGADOR
                                explosoes_ativas[total_explosoes_ativas].dano_aplicado_jogador1 = false;
                                explosoes_ativas[total_explosoes_ativas].dano_aplicado_jogador2 = false;
                                total_explosoes_ativas++;
                            }
                        }
                    }
                }
            }
            break;

        case 1: // Cruz (horizontal/vertical)
            num_direcoes = 4;
            dir_x[0] = 1;  dir_y[0] = 0;
            dir_x[1] = -1; dir_y[1] = 0;
            dir_x[2] = 0;  dir_y[2] = 1;
            dir_x[3] = 0;  dir_y[3] = -1;
            break;
            
        case 2: // Estrela (horizontal/vertical/diagonal)
            num_direcoes = 8;
            dir_x[0] = 1;  dir_y[0] = 0;
            dir_x[1] = -1; dir_y[1] = 0;
            dir_x[2] = 0;  dir_y[2] = 1;
            dir_x[3] = 0;  dir_y[3] = -1;
            dir_x[4] = 1;  dir_y[4] = 1;
            dir_x[5] = 1;  dir_y[5] = -1;
            dir_x[6] = -1; dir_y[6] = 1;
            dir_x[7] = -1; dir_y[7] = -1;
            break;
            
        case 3: // Estrela + Disco (Nuke)
            int raio_disco = raio / 2;
            for (int dy = -raio_disco; dy <= raio_disco; dy++) {
                for (int dx = -raio_disco; dx <= raio_disco; dx++) {
                    if (dx*dx + dy*dy <= raio_disco*raio_disco) {
                        int nx = x + dx;
                        int ny = y + dy;
                        
                        if (nx >= 0 && nx < MAX_W && ny >= 0 && ny < MAX_H) {
                            if (mapa_colisao[ny][nx] == OBSTACULO_DESTRUTIVEL) {
                                mapa_colisao[ny][nx] = LIVRE;
                                mapa_visual[ny][nx] = ' ';
                                obstaculos_destruidos++;
                            }
                            
                            if (total_explosoes_ativas < 200) {
                                explosoes_ativas[total_explosoes_ativas].id_bomba = id_bomba;
                                explosoes_ativas[total_explosoes_ativas].x = nx;
                                explosoes_ativas[total_explosoes_ativas].y = ny;
                                explosoes_ativas[total_explosoes_ativas].timer = 30;
                                explosoes_ativas[total_explosoes_ativas].cor = config.cor_explosao;
                                explosoes_ativas[total_explosoes_ativas].ativa = true;
                                explosoes_ativas[total_explosoes_ativas].tipo_bomba = tipo_bomba;
                                explosoes_ativas[total_explosoes_ativas].dono_explosao = dono;
                                explosoes_ativas[total_explosoes_ativas].dano = config.dano;
                                // INICIALIZAR CONTROLE DE DANO POR JOGADOR
                                explosoes_ativas[total_explosoes_ativas].dano_aplicado_jogador1 = false;
                                explosoes_ativas[total_explosoes_ativas].dano_aplicado_jogador2 = false;
                                total_explosoes_ativas++;
                            }
                        }
                    }
                }
            }
            
            num_direcoes = 8;
            dir_x[0] = 1;  dir_y[0] = 0;
            dir_x[1] = -1; dir_y[1] = 0;
            dir_x[2] = 0;  dir_y[2] = 1;
            dir_x[3] = 0;  dir_y[3] = -1;
            dir_x[4] = 1;  dir_y[4] = 1;
            dir_x[5] = 1;  dir_y[5] = -1;
            dir_x[6] = -1; dir_y[6] = 1;
            dir_x[7] = -1; dir_y[7] = -1;
            break;
    }
    
    // Para formatos 1, 2 e parte do 3, propagar nas direções
    if (formato != 0) {
        for (int d = 0; d < num_direcoes; d++) {
            for (int r = 1; r <= raio; r++) {
                int nx = x + dir_x[d] * r;
                int ny = y + dir_y[d] * r;
                
                if (nx < 0 || nx >= MAX_W || ny < 0 || ny >= MAX_H) {
                    break;
                }
                
                if (mapa_colisao[ny][nx] == PAREDE_FIXA) {
                    break;
                }
                
                if (mapa_colisao[ny][nx] == OBSTACULO_DESTRUTIVEL) {
                    mapa_colisao[ny][nx] = LIVRE;
                    mapa_visual[ny][nx] = ' ';
                    obstaculos_destruidos++;
                }
                
                // Adicionar explosão visual
                if (total_explosoes_ativas < 200) {
                    explosoes_ativas[total_explosoes_ativas].id_bomba = id_bomba;
                    explosoes_ativas[total_explosoes_ativas].x = nx;
                    explosoes_ativas[total_explosoes_ativas].y = ny;
                    explosoes_ativas[total_explosoes_ativas].timer = 30;
                    explosoes_ativas[total_explosoes_ativas].cor = config.cor_explosao;
                    explosoes_ativas[total_explosoes_ativas].ativa = true;
                    explosoes_ativas[total_explosoes_ativas].tipo_bomba = tipo_bomba;
                    explosoes_ativas[total_explosoes_ativas].dono_explosao = dono;
                    explosoes_ativas[total_explosoes_ativas].dano = config.dano;
                    // INICIALIZAR CONTROLE DE DANO POR JOGADOR
                    explosoes_ativas[total_explosoes_ativas].dano_aplicado_jogador1 = false;
                    explosoes_ativas[total_explosoes_ativas].dano_aplicado_jogador2 = false;
                    total_explosoes_ativas++;
                }
                
                if (mapa_colisao[ny][nx] == OBSTACULO_DESTRUTIVEL) {
                    break;
                }
            }
        }
    }
    
    // Atualizar estatísticas globais
    obstaculos_destruidos_ultima_explosao = obstaculos_destruidos;
    dono_ultima_explosao = dono;
}

// Aplicar dano de explosão
// Altere a função:
void aplicar_dano_explosao(Player *jogador, int dano) {
    // Se o jogador está invulnerável, não aplica dano
    if (jogador->invulneravel) {
        return;
    }
    
    int vida_anterior = jogador->vida;
    jogador->vida -= dano;
    if (jogador->vida < 0) jogador->vida = 0;
    
    // AGORA INCREMENTAR DANO SOFRIDO AQUI
    jogador->dano_sofrido += dano;
    
    // Ativar invulnerabilidade por 30 frames (1 segundo)
    jogador->invulneravel = true;
    jogador->iframes = 30;
    
    // Verificar se morreu (mortes já são contadas em verificar_colisao_explosao_completa)
    // Mas mantemos a verificação para segurança
    if (jogador->vida <= 0 && vida_anterior > 0) {
        jogador->mortes++;
    }
}

// Verificar colisão de explosão com jogadores
// Verificar colisão de explosão com jogadores - VERSÃO CORRIGIDA
// Verificar colisão de explosão com jogadores - VERSÃO SUPER SIMPLIFICADA
void verificar_colisao_explosao_completa(Player *p1, Player *p2, int offset_x, int offset_y) {
    for (int i = 0; i < total_explosoes_ativas; i++) {
        if (explosoes_ativas[i].ativa) {
            int explosao_x = offset_x + explosoes_ativas[i].x;
            int explosao_y = offset_y + explosoes_ativas[i].y;
            int dono_explosao = explosoes_ativas[i].dono_explosao;
            int dano = explosoes_ativas[i].dano;
            
            // Para jogador 1
            if (!explosoes_ativas[i].dano_aplicado_jogador1 && 
                abs(p1->x - explosao_x) <= 1 && abs(p1->y - explosao_y) <= 1) {
                
                int dano_anterior_p1 = p1->dano_sofrido;
                int vida_anterior_p1 = p1->vida;
                
                aplicar_dano_explosao(p1, dano);
                explosoes_ativas[i].dano_aplicado_jogador1 = true;
                
                // Se o dano foi aplicado (ou seja, dano_sofrido aumentou)
                if (p1->dano_sofrido > dano_anterior_p1) {
                    int dano_aplicado = p1->dano_sofrido - dano_anterior_p1;
                    
                    if (dono_explosao == 2) {
                        p2->dano_causado += dano_aplicado;
                        p2->cont_dano += dano_aplicado;
                        
                        if (p1->vida <= 0 && vida_anterior_p1 > 0) {
                            p2->kills++;
                            p2->cont_vitorias++;
                        }
                    }
                }
            }
            
            // Para jogador 2
            if (!explosoes_ativas[i].dano_aplicado_jogador2 && 
                abs(p2->x - explosao_x) <= 1 && abs(p2->y - explosao_y) <= 1) {
                
                int dano_anterior_p2 = p2->dano_sofrido;
                int vida_anterior_p2 = p2->vida;
                
                aplicar_dano_explosao(p2, dano);
                explosoes_ativas[i].dano_aplicado_jogador2 = true;
                
                // Se o dano foi aplicado (ou seja, dano_sofrido aumentou)
                if (p2->dano_sofrido > dano_anterior_p2) {
                    int dano_aplicado = p2->dano_sofrido - dano_anterior_p2;
                    
                    if (dono_explosao == 1) {
                        p1->dano_causado += dano_aplicado;
                        p1->cont_dano += dano_aplicado;
                        
                        if (p2->vida <= 0 && vida_anterior_p2 > 0) {
                            p1->kills++;
                            p1->cont_vitorias++;
                        }
                    }
                }
            }
        }
    }
}
// Desenhar bombas
void desenhar_bombas(int offset_x, int offset_y) {
    for (int i = 0; i < total_bombas_ativas; i++) {
        if (bombas_ativas[i].ativa && !bombas_ativas[i].explodindo) {
            ConfigBomba config = obter_config_bomba(bombas_ativas[i].tipo);
            mvprintw(offset_y + bombas_ativas[i].y, 
                    offset_x + bombas_ativas[i].x, 
                    "%s", config.emoji);
        }
    }
}