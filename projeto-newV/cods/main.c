#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

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
#include "../includes/ranking_menu.h"

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
        clear();
        refresh();
        
        // Menu principal
        int opcao_menu_principal = 0;
        int sair_menu = 0;
        
        while (!sair_menu) {
            opcao_menu_principal = mostrar_menu_principal();
            
            switch (opcao_menu_principal) {
                case 1: 
                    mostrar_tela_boas_vindas(user_id);
                    // Jogar
                    executar_jogo();
                    break;
                    
                case 2: // Ver Ranking
                    mostrar_menu_ranking_completo();
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
    
    // Inicializar cores se não estiverem inicializadas
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    
    while (1) {
        clear();
        
        // Título
        attron(A_BOLD | COLOR_PAIR(5));
        mvprintw(2, 2, "╔═══════════════════════════════════════════════════╗");
        mvprintw(3, 2, "║            🎮 BOMBERMAN - MENU PRINCIPAL 🎮         ║");
        mvprintw(4, 2, "╚═══════════════════════════════════════════════════╝");
        attroff(A_BOLD | COLOR_PAIR(5));
        
        // Instrução
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(12, 4, "Escolha uma opção: ");
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        // Destacar opção selecionada COM MELHOR CONTRASTE
        for (int i = 0; i < 3; i++) {
            if (i == opcao) {
                // Opção selecionada - destaque forte
                attron(A_BOLD | A_REVERSE | COLOR_PAIR(4)); // VERDE INVERTIDO para destaque máximo
                mvprintw(7 + i, 2, "▶"); // Usa seta maior
                attroff(A_BOLD | A_REVERSE | COLOR_PAIR(4));
            } else {
                // Opção não selecionada - aparência normal
                attron(COLOR_PAIR(1));
                mvprintw(7 + i, 2, " ");
                attroff(COLOR_PAIR(1));
            }
        }
        
        // Texto das opções com destaque adequado
        if (opcao == 0) {
            attron(A_BOLD | COLOR_PAIR(5)); // CIANO em negrito para selecionado
        } else {
            attron(COLOR_PAIR(5)); // CIANO normal
        }
        mvprintw(7, 4, "1. 🎯 Jogar");
        if (opcao == 0) attroff(A_BOLD | COLOR_PAIR(5));
        else attroff(COLOR_PAIR(5));
        
        if (opcao == 1) {
            attron(A_BOLD | COLOR_PAIR(3)); // AMARELO em negrito para selecionado
        } else {
            attron(COLOR_PAIR(3)); // AMARELO normal
        }
        mvprintw(8, 4, "2. 📊 Ver Ranking");
        if (opcao == 1) attroff(A_BOLD | COLOR_PAIR(3));
        else attroff(COLOR_PAIR(3));
        
        if (opcao == 2) {
            attron(A_BOLD | COLOR_PAIR(1)); // VERMELHO em negrito para selecionado
        } else {
            attron(COLOR_PAIR(1)); // VERMELHO normal
        }
        mvprintw(9, 4, "3. 🚪 Sair");
        if (opcao == 2) attroff(A_BOLD | COLOR_PAIR(1));
        else attroff(COLOR_PAIR(1));
        
        // Informações adicionais
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(15, 4, "📝 Dica:");
        attroff(COLOR_PAIR(4) | A_BOLD);
        
        attron(COLOR_PAIR(2));
        mvprintw(16, 6, "Use ↑↓ para navegar, ENTER para selecionar");
        mvprintw(17, 6, "Ou pressione 1, 2, 3 diretamente");
        attroff(COLOR_PAIR(2));
        
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
            case 27: // ESC também sai
                return 3;
        }
    }
}

// Menu completo de ranking com múltiplas opções de visualização
void mostrar_menu_ranking_completo(void) {
    // Inicializar cores se não estiverem inicializadas
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    
    // Carregar dados do arquivo
    RankingEntry *ranking_array = NULL;
    int count = 0;
    bool dados_carregados = ler_dados_arquivo("data.txt", &ranking_array, &count);
    
    if (dados_carregados && count > 0) {
        // Menu para escolher tipo de visualização
        int opcao_visualizacao = 0;
        int sair_ranking = 0;
        
        while (!sair_ranking) {
            clear();
            
            // Título do menu de visualização
            attron(A_BOLD | COLOR_PAIR(5));
            mvprintw(2, 2, "╔═══════════════════════════════════════════════════╗");
            mvprintw(3, 2, "║              📊 TIPO DE VISUALIZAÇÃO 📊            ║");
            mvprintw(4, 2, "╚═══════════════════════════════════════════════════╝");
            attroff(A_BOLD | COLOR_PAIR(5));
            
            // Instrução
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(13, 4, "Selecione uma visualização: ");
            attroff(COLOR_PAIR(3) | A_BOLD);
            
            // Destacar opção selecionada COM MELHOR CONTRASTE
            for (int i = 0; i < 4; i++) {
                if (i == opcao_visualizacao) {
                    // Opção selecionada - destaque forte
                    attron(A_BOLD | A_REVERSE | COLOR_PAIR(4)); // VERDE INVERTIDO para destaque máximo
                    mvprintw(7 + i, 2, "▶"); // Usa seta maior
                    attroff(A_BOLD | A_REVERSE | COLOR_PAIR(4));
                } else {
                    // Opção não selecionada - aparência normal
                    attron(COLOR_PAIR(1));
                    mvprintw(7 + i, 2, " ");
                    attroff(COLOR_PAIR(1));
                }
            }
            
            // Texto das opções com destaque adequado
            if (opcao_visualizacao == 0) {
                attron(A_BOLD | COLOR_PAIR(5));
            } else {
                attron(COLOR_PAIR(5));
            }
            mvprintw(7, 4, "1. 📋 Tabela tradicional");
            if (opcao_visualizacao == 0) attroff(A_BOLD | COLOR_PAIR(5));
            else attroff(COLOR_PAIR(5));
            
            if (opcao_visualizacao == 1) {
                attron(A_BOLD | COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(3));
            }
            mvprintw(8, 4, "2. 🌳 Árvore B+ (Visualização didática)");
            if (opcao_visualizacao == 1) attroff(A_BOLD | COLOR_PAIR(3));
            else attroff(COLOR_PAIR(3));
            
            if (opcao_visualizacao == 2) {
                attron(A_BOLD | COLOR_PAIR(2));
            } else {
                attron(COLOR_PAIR(2));
            }
            mvprintw(9, 4, "3. 🏗️  Árvore B+ Real (Estrutura interna)");
            if (opcao_visualizacao == 2) attroff(A_BOLD | COLOR_PAIR(2));
            else attroff(COLOR_PAIR(2));
            
            if (opcao_visualizacao == 3) {
                attron(A_BOLD | COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(1));
            }
            mvprintw(10, 4, "4. 🔙 Voltar ao Menu Principal");
            if (opcao_visualizacao == 3) attroff(A_BOLD | COLOR_PAIR(1));
            else attroff(COLOR_PAIR(1));
            
            // Informação sobre os dados
            attron(COLOR_PAIR(4));
            mvprintw(16, 4, "📈 Dados carregados: %d jogadores", count);
            attroff(COLOR_PAIR(4));
            
            // Exemplos dos top 3
            if (count >= 3) {
                ordenar_ranking(ranking_array, count, RANKING_DANO);
                attron(COLOR_PAIR(5));
                mvprintw(18, 4, "🏆 Top 3 em dano:");
                attron(COLOR_PAIR(3) | A_BOLD);
                mvprintw(19, 6, "🥇 %s: %d dano", ranking_array[0].nome, ranking_array[0].stats.cont_dano);
                attron(COLOR_PAIR(5) | A_BOLD);
                mvprintw(20, 6, "🥈 %s: %d dano", ranking_array[1].nome, ranking_array[1].stats.cont_dano);
                attron(COLOR_PAIR(1) | A_BOLD);
                mvprintw(21, 6, "🥉 %s: %d dano", ranking_array[2].nome, ranking_array[2].stats.cont_dano);
            }
            
            refresh();
            
            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    opcao_visualizacao = (opcao_visualizacao - 1 + 4) % 4;
                    break;
                case KEY_DOWN:
                    opcao_visualizacao = (opcao_visualizacao + 1) % 4;
                    break;
                case '\n':
                case KEY_ENTER:
                    processar_opcao_ranking(opcao_visualizacao, ranking_array, count);
                    if (opcao_visualizacao == 3) { // Se escolheu "Voltar"
                        sair_ranking = 1;
                    }
                    break;
                case '1':
                    processar_opcao_ranking(0, ranking_array, count);
                    break;
                case '2':
                    processar_opcao_ranking(1, ranking_array, count);
                    break;
                case '3':
                    processar_opcao_ranking(2, ranking_array, count);
                    break;
                case '4':
                    sair_ranking = 1;
                    break;
                case 27: // ESC - volta ao menu principal
                    sair_ranking = 1;
                    break;
            }
        }
        
        liberar_array_ranking(ranking_array);
    } else {
        // Se não houver dados, mostrar mensagem e opção de voltar
        clear();
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(10, 20, "📭 Nenhum dado de ranking disponível!");
        mvprintw(11, 15, "Jogue algumas partidas para gerar estatísticas");
        attroff(A_BOLD | COLOR_PAIR(3));
        
        attron(COLOR_PAIR(5));
        mvprintw(15, 20, "Pressione qualquer tecla para voltar...");
        attroff(COLOR_PAIR(5));
        
        refresh();
        getch(); // Espera qualquer tecla
    }
    
    clear();
}

// Processa a opção selecionada no menu de ranking
void processar_opcao_ranking(int opcao, RankingEntry *ranking_array, int count) {
    switch (opcao) {
        case 0: // Tabela tradicional
            mostrar_tela_ranking();
            break;
            
        case 1: // Árvore B+ didática
            mostrar_arvore_bplus(ranking_array, count, RANKING_DANO);
            break;
            
        case 2: // Árvore B+ real
            {
                // Criar árvore B+ real com os dados
                BPTree *arvore_real = bptree_create();
                
                if (arvore_real) {
                    // Inserir todos os dados na árvore
                    for (int i = 0; i < count; i++) {
                        Stats stats = {
                            ranking_array[i].stats.vida,
                            ranking_array[i].stats.cont_vitorias,
                            ranking_array[i].stats.distancia_percorrida,
                            ranking_array[i].stats.cont_dano
                        };
                        bptree_insert(arvore_real, ranking_array[i].nome, stats);
                    }
                    
                    // Mostrar menu da árvore real
                    mostrar_menu_arvore_ranking(arvore_real);
                    
                    // Liberar memória da árvore
                    bptree_free(arvore_real);
                } else {
                    // Se falhar ao criar árvore
                    clear();
                    attron(A_BOLD | COLOR_PAIR(3));
                    mvprintw(10, 20, "❌ Erro ao criar árvore B+!");
                    mvprintw(12, 20, "Pressione qualquer tecla para voltar...");
                    attroff(A_BOLD | COLOR_PAIR(3));
                    refresh();
                    getch();
                }
            }
            break;
            
        case 3: // Voltar - nada a fazer, será tratado no menu
            break;
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