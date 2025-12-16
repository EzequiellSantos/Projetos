#ifndef PLAYER_H
#define PLAYER_H

#include "bomb_types.h"
#include <stdbool.h>

// Estrutura do player
typedef struct Player {
    // Estatísticas básicas
    int vida;
    int cont_vitorias;
    int cont_dano;
    int cor;
    int ataque;
    int x, y;
    char nome[50];
    const char *emoji;
    
    // Novas estatísticas
    int bombas_jogadas;
    int obstaculos_destruidos;
    int itens_pegos;
    int dano_causado;
    int dano_sofrido;
    int distancia_percorrida;
    int kills;
    int mortes;
    
    // Para cálculo de distância
    int ultima_pos_x;
    int ultima_pos_y;
    
    // Sistema de i-frames
    int iframes;
    bool invulneravel;
    
    // Sistema de bombas
    TipoBomba bomba_atual;
    int quantidade_bomba_atual;
    int cooldown_bomba;
    int dono;
} Player;

void init_player(Player *p, int x, int y, int cor, const char *emoji, const char *nome);

#endif