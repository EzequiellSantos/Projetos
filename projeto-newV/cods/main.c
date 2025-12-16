#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../includes/game_over.h"
#include "../includes/player.h"
#include "../includes/menu.h"
#include "../includes/mapa.h"
#include "../includes/bptree.h"
#include "../includes/auth.h"
#include "../includes/auth_menu.h"
#include "../includes/stats.h"
#include "../includes/bomb.h"
#include "../includes/bomb_types.h"
#include "../includes/ranking.h"
#include "../includes/database.h"

// Funções do menu de autenticação (já declaradas em auth_menu.h)
int mostrar_menu_login(void);
int realizar_login(void);
int realizar_registro(void);
void mostrar_tela_boas_vindas(int user_id);
int select_emoji(const char *emoji_list[], const char *emoji_names[], int count, int player_num);

// Função para desenhar jogador com nome
void desenhar_jogador_com_nome(Player *p);

// Função para mostrar menu principal
int mostrar_menu_principal(void);

// Função que contém o loop principal do jogo
void executar_jogo(void);

// Ponto de entrada do programa: inicializa o ambiente e gerencia o loop de menus.
int main() {
    setlocale(LC_ALL, "");
    
    int continuar_programa = 1;
    
    while (continuar_programa) {
        initscr();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        
        // Sistema de autenticação
        int user_id = -1;
        int opcao_auth;
        
        while (user_id < 0) {
            opcao_auth = mostrar_menu_login();
            
            switch (opcao_auth) {
                case 1: // Login
                    user_id = realizar_login();
                    break;
                case 2: // Registrar
                    user_id = realizar_registro();
                    break;
                case 3: // Sair
                    endwin();
                    return 0;
            }
        }
        
        // Tela de boas-vindas
        mostrar_tela_boas_vindas(user_id);
        clear();
        refresh();
        
        // Menu principal
        int opcao_menu_principal = 0;
        int sair_menu = 0;
        
        while (!sair_menu) {
            opcao_menu_principal = mostrar_menu_principal();
            
            switch (opcao_menu_principal) {
                case 1: // Jogar
                    executar_jogo();
                    break;
                    
                case 2: // Ver Ranking
                    clear();
                    start_color();
                    init_pair(1, COLOR_RED, COLOR_BLACK);
                    init_pair(2, COLOR_BLUE, COLOR_BLACK);
                    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
                    init_pair(4, COLOR_GREEN, COLOR_BLACK);
                    init_pair(5, COLOR_CYAN, COLOR_BLACK);
                    mostrar_tela_ranking();
                    clear();
                    break;
                    
                case 3: // Sair
                    sair_menu = 1;
                    continuar_programa = 0;
                    break;
            }
        }
        
        endwin();
    }
    
    return 0;
}

// Mostra o menu principal e retorna a opção selecionada (1-3).
int mostrar_menu_principal(void) {
    int opcao = 0;
    int ch;
    
    nodelay(stdscr, FALSE);
    
    while (1) {
        clear();
        
        // Título
        mvprintw(2, 2, "=== BOMBERMAN - MENU PRINCIPAL ===");
        
        // Opções
        mvprintw(4, 4, "1. Jogar");
        mvprintw(5, 4, "2. Ver Ranking");
        mvprintw(6, 4, "3. Sair");
        mvprintw(8, 4, "Escolha uma opcao: ");
        
        // Destacar opção selecionada
        mvprintw(4 + opcao, 3, ">");
        
        ch = getch();
        
        switch (ch) {
            case KEY_UP:
                opcao = (opcao - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                opcao = (opcao + 1) % 3;
                break;
            case '\n':
            case KEY_ENTER:
                return opcao + 1;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case 'q': return 3;
        }
    }
}

// Executa o loop principal do jogo: atualiza lógica, processa input e desenha a tela.
void executar_jogo(void) {
    // Configurar para modo não bloqueante
    nodelay(stdscr, TRUE);
    start_color();
    
    // Configurar cores
    init_pair(1, COLOR_RED,  COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Para itens
    init_pair(4, COLOR_GREEN, COLOR_BLACK);  // Para bombas
    init_pair(5, COLOR_CYAN, COLOR_BLACK);   // Para estatísticas
    
    inicializar_sistema_bombas();

    const char *emoji_list[] = {
        "😀","😎","🤖","👾","🐍",
        "🐱","🔥","💀","👽","🦊"
    };
    
    const char *emoji_names[] = {
        "Killer","Cool","GPT","C U(çí u)","Jeboia",
        "Garfield","Fire ball","Silvio Santos","Mambira","Sweetie"
    };
    
    int count = 10;
    
    // Selecionar emojis para os jogadores
    int choice1 = select_emoji(emoji_list, emoji_names, count, 1);
    int choice2 = select_emoji(emoji_list, emoji_names, count, 2);
    
    // Calcular dimensões da tela
    int screen_width = getmaxx(stdscr);
    int screen_height = getmaxy(stdscr);
    
    // Calcular layout da tela
    int stats_width = STATS_WIDTH;  // Largura de cada painel de estatísticas
    int total_stats_width = stats_width * 2;  // Ambos os lados
    
    // Calcular tamanho do mapa (3/4 do terminal, menos espaço das estatísticas)
    int mapa_largura = (screen_width - total_stats_width) * 0.85;
    int mapa_altura = screen_height * 0.75;
    
    // Limitar ao máximo definido
    if (mapa_largura > MAX_W) mapa_largura = MAX_W;
    if (mapa_altura > MAX_H) mapa_altura = MAX_H;
    
    // Calcular offsets
    int offset_x = stats_width + (screen_width - total_stats_width - mapa_largura) / 2;
    int offset_y = (screen_height - mapa_altura) / 2;
    
    // Posições iniciais para as estatísticas
    int stats1_x = 1;  // Esquerda
    int stats2_x = screen_width - stats_width - 1;  // Direita
    int stats_y = 1;  // Topo
    
    // Inicializar mapa
    inicializar_mapa(mapa_altura, mapa_largura);
    
    // Posicionar jogadores em áreas seguras
    Player p1, p2;
    init_player(&p1, offset_x + 2, offset_y + 2, 1, 
                emoji_list[choice1], emoji_names[choice1]);
    init_player(&p2, offset_x + mapa_largura - 3, 
                offset_y + mapa_altura - 3, 2, 
                emoji_list[choice2], emoji_names[choice2]);
    
    // Criar B+ tree
    BPTree *tree = bptree_create();
    
    // Carregar dados existentes do disco
    carregar_dados_disco(tree);
    
    // Loop principal do jogo
    int jogo_rodando = 1;
    while (jogo_rodando) {
        clear();
        
        // Atualizar itens (spawn e temporizador)
        atualizar_itens(mapa_altura, mapa_largura);

        // Atualizar bombas
        atualizar_bombas(mapa_altura, mapa_largura, &p1, &p2);

        // Desenhar mapa
        desenhar_mapa(offset_x, offset_y, mapa_altura, mapa_largura);
        
        // Desenhar itens
        desenhar_itens(offset_x, offset_y);

        // Desenhar bombas e explosões
        desenhar_bombas(offset_x, offset_y);
        desenhar_explosoes(offset_x, offset_y);

        // Verificar colisão de explosões
        verificar_colisao_explosao_completa(&p1, &p2, offset_x, offset_y);

        // Atualizar i-frames dos jogadores
        if (p1.invulneravel) {
            p1.iframes--;
            if (p1.iframes <= 0) {
                p1.invulneravel = false;
                p1.iframes = 0;
            }
        }
        
        if (p2.invulneravel) {
            p2.iframes--;
            if (p2.iframes <= 0) {
                p2.invulneravel = false;
                p2.iframes = 0;
            }
        }
        
        // Atualizar cooldown
        if (p1.cooldown_bomba > 0) p1.cooldown_bomba--;
        if (p2.cooldown_bomba > 0) p2.cooldown_bomba--;
        
        // Desenhar painéis de estatísticas
        desenhar_stats_player(&p1, stats1_x, stats_y, 1);
        desenhar_stats_player(&p2, stats2_x, stats_y, 2);

        // Desenhar borda ao redor do mapa
        attron(COLOR_PAIR(5));
        for (int i = 0; i < mapa_altura; i++) {
            if (i == 0 || i == mapa_altura - 1) {
                for (int j = 0; j < mapa_largura; j++) {
                    mvaddch(offset_y + i, offset_x + j, '-');
                }
            } else {
                mvaddch(offset_y + i, offset_x, '|');
                mvaddch(offset_y + i, offset_x + mapa_largura - 1, '|');
            }
        }
        mvaddch(offset_y, offset_x, '+');
        mvaddch(offset_y, offset_x + mapa_largura - 1, '+');
        mvaddch(offset_y + mapa_altura - 1, offset_x, '+');
        mvaddch(offset_y + mapa_altura - 1, offset_x + mapa_largura - 1, '+');
        attroff(COLOR_PAIR(5));
        
        int ch = getch();
        int novo_x1 = p1.x, novo_y1 = p1.y;
        int novo_x2 = p2.x, novo_y2 = p2.y;
        
        // Processar input e calcular novas posições
        switch (ch) {
            case 'w': novo_y1--; break;
            case 's': novo_y1++; break;
            case 'a': novo_x1--; break;
            case 'd': novo_x1++; break;
            
            case KEY_UP:    novo_y2--; break;
            case KEY_DOWN:  novo_y2++; break;
            case KEY_LEFT:  novo_x2--; break;
            case KEY_RIGHT: novo_x2++; break;
            
            case ' ':
                if (p1.cooldown_bomba == 0) {
                    plantar_bomba(&p1, offset_x, offset_y);
                }
                break;
                
            case '/':
                if (p2.cooldown_bomba == 0) {
                    plantar_bomba(&p2, offset_x, offset_y);
                }
                break;
            
            case 'q':
                jogo_rodando = 0;
                break;
                
            case 27: // ESC
                jogo_rodando = 0;
                break;
        }
        
        // Verificar colisão usando as NOVAS posições
        if (posicao_valida(novo_x1 - offset_x, novo_y1 - offset_y)) {
            // Atualizar distância percorrida
            if (p1.x != novo_x1 || p1.y != novo_y1) {
                int dx = abs(novo_x1 - p1.x);
                int dy = abs(novo_y1 - p1.y);
                p1.distancia_percorrida += dx + dy;
            }
            
            p1.x = novo_x1;
            p1.y = novo_y1;
        }
        
        if (posicao_valida(novo_x2 - offset_x, novo_y2 - offset_y)) {
            // Atualizar distância percorrida
            if (p2.x != novo_x2 || p2.y != novo_y2) {
                int dx = abs(novo_x2 - p2.x);
                int dy = abs(novo_y2 - p2.y);
                p2.distancia_percorrida += dx + dy;
            }
            
            p2.x = novo_x2;
            p2.y = novo_y2;
        }
        
        // Verificar se jogadores pegaram itens
        for (int i = 0; i < total_itens; i++) {
            if (itens_mapa[i].ativo) {
                int item_x = offset_x + itens_mapa[i].x;
                int item_y = offset_y + itens_mapa[i].y;
                
                if (p1.x == item_x && p1.y == item_y) {
                    itens_mapa[i].ativo = false;
                    p1.itens_pegos++;
                    
                    // Gerar bomba surpresa
                    TipoBomba nova_bomba = gerar_bomba_surpresa();
                    p1.bomba_atual = nova_bomba;
                    p1.quantidade_bomba_atual = 10;
                    
                    // Mostrar mensagem
                    ConfigBomba config = obter_config_bomba(nova_bomba);
                    mvprintw(0, 0, "Player 1 pegou: %s!", config.nome);
                } else if (p2.x == item_x && p2.y == item_y) {
                    itens_mapa[i].ativo = false;
                    p2.itens_pegos++;
                    
                    // Gerar bomba surpresa
                    TipoBomba nova_bomba = gerar_bomba_surpresa();
                    p2.bomba_atual = nova_bomba;
                    p2.quantidade_bomba_atual = 10;
                    
                    // Mostrar mensagem
                    ConfigBomba config = obter_config_bomba(nova_bomba);
                    mvprintw(0, 0, "Player 2 pegou: %s!", config.nome);
                }
            }
        }
        
        // Manter jogadores dentro dos limites do mapa visível
        if (p1.x < offset_x + 1) p1.x = offset_x + 1;
        if (p1.y < offset_y + 1) p1.y = offset_y + 1;
        if (p1.x > offset_x + mapa_largura - 2) p1.x = offset_x + mapa_largura - 2;
        if (p1.y > offset_y + mapa_altura - 2) p1.y = offset_y + mapa_altura - 2;
        
        if (p2.x < offset_x + 1) p2.x = offset_x + 1;
        if (p2.y < offset_y + 1) p2.y = offset_y + 1;
        if (p2.x > offset_x + mapa_largura - 2) p2.x = offset_x + mapa_largura - 2;
        if (p2.y > offset_y + mapa_altura - 2) p2.y = offset_y + mapa_altura - 2;
        
        // Desenhar jogadores com seus nomes
        desenhar_jogador_com_nome(&p1);
        desenhar_jogador_com_nome(&p2);
        
        // Info na tela
        mvprintw(0, stats_width + (screen_width - total_stats_width)/2, "=== BOMBERMAN ===");
        
        refresh();
        
        // Verificar se o jogo acabou (alguém chegou a 0 de vida)
        if (p1.vida <= 0 || p2.vida <= 0) {
            // Criar estatísticas finais desta partida
            Stats up1 = { 
                p1.vida, 
                p1.cont_vitorias,  // Número de vitórias nesta partida
                p1.distancia_percorrida,  // Distância percorrida nesta partida
                p1.cont_dano  // Dano causado nesta partida
            };
            
            Stats up2 = { 
                p2.vida, 
                p2.cont_vitorias,
                p2.distancia_percorrida,
                p2.cont_dano
            };
            
            // Inserir ou atualizar estatísticas na árvore
            inserir_ou_atualizar_stats(tree, p1.nome, up1);
            inserir_ou_atualizar_stats(tree, p2.nome, up2);
            
            // Salvar no disco
            salvar_dados_disco(tree);
            bptree_free(tree);
            
            // Mostrar tela de fim de jogo
            mostrar_tela_game_over(&p1, &p2);
            
            // Processar input (apenas 1 ENTER) - ENTER voltará ao menu
            processar_input_game_over();
            
            // Terminar o jogo atual
            jogo_rodando = 0;
        }
        
        // Pequena pausa para 30 FPS
        napms(33);
    }
    
    // Limpar a tela
    clear();
}

// Desenha o jogador `p` junto com seu nome, cooldown e efeitos visuais.
void desenhar_jogador_com_nome(Player *p) {
    // Se estiver invulnerável, desenhar com efeito piscante
    if (p->invulneravel) {
        // Piscar a cada 10 frames (5 vezes por segundo)
        if ((p->iframes / 5) % 2 == 0) {
            attron(A_BOLD | COLOR_PAIR(p->cor));
        } else {
            attron(COLOR_PAIR(p->cor));
        }
    } else {
        attron(COLOR_PAIR(p->cor));
    }
    
    // Desenhar nome acima do emoji
    int nome_len = strlen(p->nome);
    int nome_x = p->x - nome_len/2;
    
    // Ajustar para não sair da tela
    int max_x = getmaxx(stdscr);
    if (nome_x < 0) nome_x = 0;
    if (nome_x + nome_len > max_x) nome_x = max_x - nome_len;
    
    // Desenhar nome (na linha acima do emoji)
    mvprintw(p->y - 1, nome_x, "%s", p->nome);
    
    // Se estiver em cooldown, mostrar o tempo restante em segundos
    if (p->cooldown_bomba > 0) {
        int segundos = (p->cooldown_bomba + 29) / 30; // Arredonda para cima
        mvprintw(p->y + 1, p->x - 1, "%d", segundos);
    }
    
    // Se estiver invulnerável, mostrar "I"
    if (p->invulneravel) {
        mvprintw(p->y + 1, p->x, "I");
    }
    
    // Desenhar emoji
    mvprintw(p->y, p->x, "%s", p->emoji);
    
    // Desligar atributos
    if (p->invulneravel) {
        if ((p->iframes / 5) % 2 == 0) {
            attroff(A_BOLD | COLOR_PAIR(p->cor));
        } else {
            attroff(COLOR_PAIR(p->cor));
        }
    } else {
        attroff(COLOR_PAIR(p->cor));
    }
}