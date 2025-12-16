#include "../includes/player.h"
#include "../includes/bomb.h"
#include <string.h>

// funções inGame

/*
* Inicializa os campos de um `Player` com valores padrão e posições iniciais.
* Configura vida, estatísticas, tipo de bomba e nome (se fornecido).
*/
void init_player(Player *p, int x, int y, int cor, const char *emoji, const char *nome) {
    p->vida = 100;
    p->cont_vitorias = 0;
    p->cont_dano = 0;
    p->cor = cor;
    p->ataque = 0;
    p->x = x;
    p->y = y;
    p->ultima_pos_x = x;
    p->ultima_pos_y = y;
    p->emoji = emoji;
    
    // Inicializar novas estatísticas
    p->bombas_jogadas = 0;
    p->obstaculos_destruidos = 0;
    p->itens_pegos = 0;
    p->dano_causado = 0;
    p->dano_sofrido = 0;
    p->distancia_percorrida = 0;
    p->kills = 0;
    p->mortes = 0;
    
    // Sistema de i-frames
    p->iframes = 0;
    p->invulneravel = false;
    
    // Sistema de bombas
    p->bomba_atual = BOMBA_INICIAL;
    p->quantidade_bomba_atual = -1;  // Ilimitada para bomba inicial
    p->cooldown_bomba = 0;
    p->dono = (cor == 1) ? 1 : 2;  // Assumindo que a cor 1 é jogador1, 2 é jogador2
    
    if (nome) {
        strncpy(p->nome, nome, sizeof(p->nome)-1);
        p->nome[sizeof(p->nome)-1] = '\0';
    } else {
        p->nome[0] = '\0';
    }
}