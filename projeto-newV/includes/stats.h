#ifndef STATS_H
#define STATS_H

#include "player.h"

// Dimensões da tabela de estatísticas
#define STATS_WIDTH 25  // Largura de cada painel de estatísticas
#define STATS_HEIGHT 20 // Altura máxima

// Funções para desenhar estatísticas
void desenhar_stats_player(Player *p, int start_x, int start_y, int player_num);
void atualizar_distancia(Player *p);

#endif