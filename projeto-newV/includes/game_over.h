#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "player.h"

// Dimensões da tela de fim de jogo
#define GAME_OVER_WIDTH 80
#define GAME_OVER_HEIGHT 24

// Funções para a tela de fim de jogo
void mostrar_tela_game_over(Player *p1, Player *p2);
int processar_input_game_over();

#endif