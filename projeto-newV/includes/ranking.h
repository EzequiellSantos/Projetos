#ifndef RANKING_H
#define RANKING_H

#include "bptree.h"
#include <stdbool.h>

// Opções de ordenação
typedef enum {
    RANKING_DANO = 0,
    RANKING_VITORIAS = 1,
    RANKING_DISTANCIA = 2
} RankingCriterio;

// Estrutura para entrada do ranking
typedef struct {
    char nome[50];
    Stats stats;
    int posicao;
} RankingEntry;

// Funções do ranking
void mostrar_tela_ranking(void);
int carregar_ranking_para_array(BPTree *tree, RankingEntry **array);
void ordenar_ranking(RankingEntry *array, int n, RankingCriterio criterio);
void liberar_array_ranking(RankingEntry *array);
bool ler_dados_arquivo(const char *filename, RankingEntry **array, int *count);

#endif