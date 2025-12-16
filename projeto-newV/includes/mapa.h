#ifndef MAPA_H
#define MAPA_H

#include <stdbool.h>
#include <ncurses.h>

#define MAX_H 50
#define MAX_W 100

// Tipos de células
#define LIVRE 0
#define PAREDE_FIXA 1
#define OBSTACULO_DESTRUTIVEL 2
#define BOMBA 3

// Estrutura para itens
typedef struct {
    int x, y;
    int tipo;  // 0: bomba+, 1: alcance+, 2: velocidade+
    int tempo_restante;
    bool ativo;
} ItemMapa;

// Variáveis globais
extern int mapa_colisao[MAX_H][MAX_W];
extern chtype mapa_visual[MAX_H][MAX_W];
extern ItemMapa itens_mapa[20];
extern int total_itens;

// Funções
void inicializar_mapa(int altura, int largura);
void desenhar_mapa(int offset_x, int offset_y, int altura, int largura);
bool posicao_valida(int x, int y);

// Funções para itens
void spawnar_item(int altura, int largura);
void atualizar_itens(int altura, int largura);
void desenhar_itens(int offset_x, int offset_y);

#endif