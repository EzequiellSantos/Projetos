#ifndef DATABASE_H
#define DATABASE_H

#include "bptree.h"

// Funções para gerenciamento de dados persistentes
void carregar_dados_disco(BPTree *tree);
void salvar_dados_disco(BPTree *tree);
void inserir_ou_atualizar_stats(BPTree *tree, const char *nome, Stats novas_stats);

#endif