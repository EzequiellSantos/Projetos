#ifndef RANKING_MENU_H
#define RANKING_MENU_H

#include "ranking.h"
#include "bptree.h"

// Menu completo de ranking
void mostrar_menu_ranking_completo(void);

// Processa a opção selecionada no menu de ranking
void processar_opcao_ranking(int opcao, RankingEntry *ranking_array, int count);

// Declaração da função que está em bptree_visual.c
void mostrar_menu_arvore_ranking(BPTree *tree);

// Função para mostrar árvore B+ (simulada/didática)
void mostrar_arvore_bplus(RankingEntry *ranking_array, int count, RankingCriterio criterio);


#endif