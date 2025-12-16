#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    int vida;
    int cont_vitorias;
    int cont_mov;
    int cont_dano;
    int cor;
    int ataque;
    int x, y;
    char nome[50];
    const char *emoji;
} Player;

void init_player(Player *p, int x, int y, int cor, const char *emoji);

#endif
