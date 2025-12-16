#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "../includes/game_over.h"
#include "../includes/stats.h"
#include "../includes/player.h"

// Função para desenhar o quadro de estatísticas final
void desenhar_stats_final(Player *p1, Player *p2, int start_x, int start_y) {
    // Quadro do jogador 1 (esquerda)
    int stats_x1 = start_x;
    int stats_x2 = start_x + STATS_WIDTH + 10; // Espaço entre os quadros
    
    desenhar_stats_player(p1, stats_x1, start_y, 1);
    desenhar_stats_player(p2, stats_x2, start_y, 2);
}

// Função para mostrar a tela de fim de jogo
void mostrar_tela_game_over(Player *p1, Player *p2) {
    // Limpar completamente a tela
    clear();
    refresh();
    
    // Aguardar um pouco para garantir que a tela está limpa
    usleep(50000);
    
    // Limpar novamente para garantir
    clear();
    
    // Calcular dimensões centrais
    int screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);
    
    int start_x = (screen_width - GAME_OVER_WIDTH) / 2;
    int start_y = (screen_height - GAME_OVER_HEIGHT) / 2;
    
    // Desenhar fundo sólido (tela toda preta)
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            mvaddch(y, x, ' ');
        }
    }
    
    // Desenhar borda da tela
    attron(COLOR_PAIR(5) | A_BOLD);
    for (int x = start_x; x < start_x + GAME_OVER_WIDTH; x++) {
        mvaddch(start_y, x, '-');
        mvaddch(start_y + GAME_OVER_HEIGHT - 1, x, '-');
    }
    for (int y = start_y; y < start_y + GAME_OVER_HEIGHT; y++) {
        mvaddch(y, start_x, '|');
        mvaddch(y, start_x + GAME_OVER_WIDTH - 1, '|');
    }
    mvaddch(start_y, start_x, '+');
    mvaddch(start_y, start_x + GAME_OVER_WIDTH - 1, '+');
    mvaddch(start_y + GAME_OVER_HEIGHT - 1, start_x, '+');
    mvaddch(start_y + GAME_OVER_HEIGHT - 1, start_x + GAME_OVER_WIDTH - 1, '+');
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // Título
    attron(A_BOLD | COLOR_PAIR(3));
    mvprintw(start_y + 1, start_x + (GAME_OVER_WIDTH/2) - 10, "🎮 FIM DE JOGO 🎮");
    attroff(A_BOLD | COLOR_PAIR(3));
    
    // Determinar vencedor e perdedor
    Player *vencedor = NULL;
    Player *perdedor = NULL;
    int empate = 0;
    
    if (p1->vida > 0 && p2->vida > 0) {
        // Ambos com vida (não deveria acontecer normalmente, mas pode ser usado se houver tempo limite)
        empate = 1;
    } else if (p1->vida > 0) {
        vencedor = p1;
        perdedor = p2;
    } else if (p2->vida > 0) {
        vencedor = p2;
        perdedor = p1;
    } else {
        // Ambos com 0 de vida = empate
        empate = 1;
    }
    
    int linha_atual = start_y + 3;
    
    // Mensagens de resultado
    if (empate) {
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(linha_atual++, start_x + (GAME_OVER_WIDTH/2) - 7, "🤝 EMPATE! 🤝");
        attroff(A_BOLD | COLOR_PAIR(3));
    } else {
        // Mensagem de vitória (verde)
        attron(A_BOLD | COLOR_PAIR(4));
        char msg_vitoria[100];
        snprintf(msg_vitoria, sizeof(msg_vitoria), "🏆 VITORIA: %s %s 🏆", vencedor->nome, vencedor->emoji);
        mvprintw(linha_atual, start_x + (GAME_OVER_WIDTH/2) - strlen(msg_vitoria)/2, "%s", msg_vitoria);
        attroff(A_BOLD | COLOR_PAIR(4));
        linha_atual++;
        
        // Mensagem de derrota (vermelho)
        attron(A_BOLD | COLOR_PAIR(1));
        char msg_derrota[100];
        snprintf(msg_derrota, sizeof(msg_derrota), "💀 DERROTA: %s %s 💀", perdedor->nome, perdedor->emoji);
        mvprintw(linha_atual, start_x + (GAME_OVER_WIDTH/2) - strlen(msg_derrota)/2, "%s", msg_derrota);
        attroff(A_BOLD | COLOR_PAIR(1));
        linha_atual++;
    }
    
    linha_atual += 2;
    
    // Desenhar estatísticas
    desenhar_stats_final(p1, p2, start_x + 5, linha_atual);
    
    linha_atual += STATS_HEIGHT + 2;
    
    // Mensagem de instrução (mais simples)
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(linha_atual, start_x + (GAME_OVER_WIDTH/2) - 18, "Pressione ENTER para voltar ao menu");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // Feedback visual de pressionar ENTER
    linha_atual += 2;
    attron(COLOR_PAIR(3) | A_BLINK);
    mvprintw(linha_atual, start_x + (GAME_OVER_WIDTH/2) - 8, "[Pressione ENTER]");
    attroff(COLOR_PAIR(3) | A_BLINK);
    
    refresh();
}

// Função para processar input na tela de fim de jogo - VERSÃO SIMPLIFICADA (1 ENTER)
int processar_input_game_over() {
    while (1) {
        int ch = getch();
        
        if (ch == '\n' || ch == KEY_ENTER) {  // ENTER
            return 0; // Retorna 0 para voltar ao menu
        }
        
        // Se ESC for pressionado, sair completamente
        if (ch == 27) {  // ESC
            return 1; // Retorna 1 para sair completamente
        }
    }
}