#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../includes/mapa.h"

// Variáveis do mapa
int mapa_colisao[MAX_H][MAX_W] = {0};
chtype mapa_visual[MAX_H][MAX_W];

// Variáveis de itens
ItemMapa itens_mapa[20];
int total_itens = 0;
int contador_spawn = 0;

// Inicializa o mapa
void inicializar_mapa(int altura, int largura) {
    srand(time(NULL));
    
    for (int i = 0; i < MAX_H; i++) {
        for (int j = 0; j < MAX_W; j++) {
            mapa_colisao[i][j] = LIVRE;
            mapa_visual[i][j] = ' ';
        }
    }
    
    // Cria bordas com caracteres ACS
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (i == 0 || i == altura-1 || j == 0 || j == largura-1) {
                mapa_colisao[i][j] = PAREDE_FIXA;
                mapa_visual[i][j] = ACS_BLOCK;
            }
        }
    }
    
    // Gera obstáculos destrutíveis (12%)
    for (int i = 2; i < altura-2; i++) {
        for (int j = 2; j < largura-2; j++) {
            // Deixa áreas de spawn livres
            if ((i < 4 && j < 4) || 
                (i > altura-5 && j > largura-5) ||
                (abs(i - altura/2) < 3 && abs(j - largura/2) < 3)) {
                continue;
            }
            
            if (rand() % 100 < 12) {
                mapa_colisao[i][j] = OBSTACULO_DESTRUTIVEL;
                mapa_visual[i][j] = ACS_CKBOARD;
            }
        }
    }
    
    // Inicializa array de itens
    for (int i = 0; i < 20; i++) {
        itens_mapa[i].ativo = false;
    }
}

// Desenha o mapa
void desenhar_mapa(int offset_x, int offset_y, int altura, int largura) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (mapa_visual[i][j] != ' ') {
                mvaddch(offset_y + i, offset_x + j, mapa_visual[i][j]);
            }
        }
    }
}

// Verifica se uma posição está dentro dos limites do mapa
bool dentro_dos_limites(int x, int y) {
    return (x >= 0 && x < MAX_W && y >= 0 && y < MAX_H);
}

// E atualize posicao_valida para:
bool posicao_valida(int x, int y) {
    if (!dentro_dos_limites(x, y)) {
        return false;
    }
    return (mapa_colisao[y][x] == LIVRE);
}

// Cria um novo item em posição aleatória
void spawnar_item(int altura, int largura) {
    if (total_itens >= 20) return;
    
    int tentativas = 0;
    while (tentativas < 50) {
        int x = rand() % (largura-4) + 2;
        int y = rand() % (altura-4) + 2;
        
        if (mapa_colisao[y][x] == LIVRE) {
            // Verifica se já não tem item nesta posição
            bool posicao_livre = true;
            for (int i = 0; i < total_itens; i++) {
                if (itens_mapa[i].ativo && 
                    itens_mapa[i].x == x && 
                    itens_mapa[i].y == y) {
                    posicao_livre = false;
                    break;
                }
            }
            
            if (posicao_livre) {
                itens_mapa[total_itens].x = x;
                itens_mapa[total_itens].y = y;
                itens_mapa[total_itens].tipo = rand() % 3;
                itens_mapa[total_itens].tempo_restante = 300; // 300 frames (~10 segundos)
                itens_mapa[total_itens].ativo = true;
                total_itens++;
                break;
            }
        }
        tentativas++;
    }
}

// Atualiza os itens (spawn e tempo)
void atualizar_itens(int altura, int largura) {
    contador_spawn++;
    
    // Spawnar novo item a cada 15 segundos (~450 frames)
    if (contador_spawn >= 450) {
        spawnar_item(altura, largura);
        contador_spawn = 0;
    }
    
    // Atualizar itens existentes
    for (int i = 0; i < total_itens; i++) {
        if (itens_mapa[i].ativo) {
            itens_mapa[i].tempo_restante--;
            if (itens_mapa[i].tempo_restante <= 0) {
                itens_mapa[i].ativo = false;
                // Remover item desativado (compactar array)
                for (int j = i; j < total_itens-1; j++) {
                    itens_mapa[j] = itens_mapa[j+1];
                }
                total_itens--;
                i--; // Revisitar mesma posição
            }
        }
    }
}

// Desenha os itens ativos
void desenhar_itens(int offset_x, int offset_y) {
    for (int i = 0; i < total_itens; i++) {
        if (itens_mapa[i].ativo) {
            attron(COLOR_PAIR(3)); // Cor diferente para itens
            mvaddch(offset_y + itens_mapa[i].y, offset_x + itens_mapa[i].x, '?');
            attroff(COLOR_PAIR(3));
        }
    }
}