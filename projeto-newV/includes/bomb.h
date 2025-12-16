#ifndef BOMBA_H
#define BOMBA_H

#include <ncurses.h>
#include <stdbool.h>
#include "bomb_types.h"

// Declaração antecipada de Player
typedef struct Player Player;

// Estrutura da bomba
typedef struct {
    int x, y;
    TipoBomba tipo;
    int timer;
    bool ativa;
    bool explodindo;
    int fase_explosao;
    int dono;
    int id; //id da bomba
} Bomba;

// Estrutura para explosão
typedef struct {
    int id_bomba;
    int x, y;
    int timer;
    int cor;
    bool ativa;
    TipoBomba tipo_bomba;
    int dono_explosao;
    int dano;
//    bool dano_aplicado;          // já existente - podemos manter para uso geral? ou não
    bool dano_aplicado_jogador1; // novo
    bool dano_aplicado_jogador2; // novo
} Explosao;

// Configurações de cada tipo de bomba
typedef struct {
    char nome[30];
    int dano;
    char emoji[5];
    int cor_explosao;
    int raio;
    int quantidade;
    int formato;
} ConfigBomba;

// Variáveis globais
extern Bomba bombas_ativas[50];
extern int total_bombas_ativas;
extern Explosao explosoes_ativas[200];
extern int total_explosoes_ativas;

// Funções
void inicializar_sistema_bombas();
ConfigBomba obter_config_bomba(TipoBomba tipo);
void plantar_bomba(Player *jogador, int offset_x, int offset_y);
void atualizar_bombas(int mapa_altura, int mapa_largura, Player *p1, Player *p2);
void desenhar_bombas(int offset_x, int offset_y);
void desenhar_explosoes(int offset_x, int offset_y);
void verificar_colisao_explosao_completa(Player *p1, Player *p2, int offset_x, int offset_y);
TipoBomba gerar_bomba_surpresa();
void aplicar_dano_explosao(Player *jogador, int dano);
void destruir_obstaculos(int x, int y, int raio, int formato, int dono, TipoBomba tipo_bomba, int id_bomba);

#endif