#include <ncurses.h>
#include <string.h>
#include <math.h>
#include "../includes/stats.h"
#include "../includes/player.h"
#include "../includes/bomb_types.h"  // Adicionar esta linha

// Função auxiliar para obter nome da bomba
static const char* obter_nome_bomba(TipoBomba tipo) {
    switch (tipo) {
        case BOMBA_INICIAL: return "Peidivea";
        case BOMBA_MEDIA:   return "Rasga-Lata";
        case BOMBA_FORTE:   return "Treme-Terra";
        case BOMBA_NUKE:    return "LgK10";
        default:            return "Desconhecida";
    }
}

// Desenha as estatísticas de um jogador
void desenhar_stats_player(Player *p, int start_x, int start_y, int player_num) {
    // Título
    attron(A_BOLD);
    if (player_num == 1) {
        attron(COLOR_PAIR(1)); // Vermelho
    } else {
        attron(COLOR_PAIR(2)); // Azul
    }
    
    mvprintw(start_y, start_x + (STATS_WIDTH/2) - 4, "PLAYER %d", player_num);
    attroff(A_BOLD);
    if (player_num == 1) {
        attroff(COLOR_PAIR(1));
    } else {
        attroff(COLOR_PAIR(2));
    }
    
    // Linha separadora
    attron(COLOR_PAIR(5));
    mvhline(start_y + 1, start_x, '-', STATS_WIDTH);
    attroff(COLOR_PAIR(5));

    int linha = start_y + 2;
    
    // Nome do jogador (login)
    mvprintw(linha++, start_x, "Mohammad: %s", p->nome);
    
    // Personagem (emoji)
    mvprintw(linha++, start_x, "Mulçumano: %s", p->emoji);
    
    // Bomba atual
    mvprintw(linha++, start_x, "Bomba: %s", obter_nome_bomba(p->bomba_atual));
    
    // Quantidade de bombas
    if (p->quantidade_bomba_atual == -1) {
        mvprintw(linha++, start_x, "Qtd: ILIMITADA");
    } else {
        mvprintw(linha++, start_x, "Qtd: %d", p->quantidade_bomba_atual);
    }
    
    // Linha separadora
    attron(COLOR_PAIR(5));
    mvhline(linha++, start_x, '-', STATS_WIDTH);
    attroff(COLOR_PAIR(5));

    // Estatísticas de vida
    attron(A_BOLD);
    mvprintw(linha++, start_x, "VIDA: %d/100", p->vida);
    attroff(A_BOLD);
    
    // Barra de vida
    int vida_barra = (p->vida * (STATS_WIDTH-10)) / 100;
    mvprintw(linha, start_x, "[");
    for (int i = 0; i < STATS_WIDTH-10; i++) {
        if (i < vida_barra) {
            if (player_num == 1) {
                attron(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
            }
            mvaddch(linha, start_x + 1 + i, '#');
            if (player_num == 1) {
                attroff(COLOR_PAIR(1));
            } else {
                attroff(COLOR_PAIR(2));
            }
        } else {
            mvaddch(linha, start_x + 1 + i, '.');
        }
    }
    mvprintw(linha, start_x + STATS_WIDTH - 9, "]");
    linha++;
    
    // Linha separadora
    attron(COLOR_PAIR(5));
    mvhline(linha++, start_x, '-', STATS_WIDTH);
    attroff(COLOR_PAIR(5));

    // Estatísticas de combate
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    mvprintw(linha++, start_x, "Dano Sofrido: %d", p->dano_sofrido);
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(linha++, start_x, "Dano Causado: %d", p->dano_causado);
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
    mvprintw(linha++, start_x, "Kills: %d", p->kills);
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvprintw(linha++, start_x, "Mortes: %d", p->mortes);
    attroff(COLOR_PAIR(2));
    attron(A_BOLD);
    
    //Linha separadora
    attron(COLOR_PAIR(5));
    mvhline(linha++, start_x, '-', STATS_WIDTH);
    attroff(COLOR_PAIR(5));
    
    // Estatísticas de jogo
    attron(A_BOLD);
    attron(COLOR_PAIR(3));
    mvprintw(linha++, start_x, "Distancia: %d cells", p->distancia_percorrida);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(4));
    mvprintw(linha++, start_x, "Bombas: %d", p->bombas_jogadas);
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(5));
    mvprintw(linha++, start_x, "Obstaculos: %d", p->obstaculos_destruidos);
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(4));
    mvprintw(linha++, start_x, "Itens: %d", p->itens_pegos);
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    mvprintw(linha++, start_x, "Vitorias: %d", p->cont_vitorias);
    attroff(COLOR_PAIR(3));
    attroff(A_BOLD);

    // Linha separadora
    attron(COLOR_PAIR(5));
    mvhline(linha++, start_x, '-', STATS_WIDTH);
    attroff(COLOR_PAIR(5));
    
    // Dano total
    attron(A_BOLD);
    mvprintw(linha++, start_x, "DANO TOTAL: %d", p->cont_dano);
    attroff(A_BOLD);
}