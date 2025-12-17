#ifndef BPTREE_H
#define BPTREE_H

#include <stdbool.h>

// Ordem default (pode ser alterada antes de compilar)
#ifndef BPTREE_ORDER
#define BPTREE_ORDER 4
#endif

// Alias usado em alguns arquivos
#define ORDER BPTREE_ORDER
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS ((ORDER/2) - 1)

typedef struct Stats {
    int vida;
    int cont_vitorias;
    int distancia_percorrida; // distância percorrida
    int cont_dano;
} Stats;

// Estrutura de nó da B+ (exposta para módulos de visualização)
typedef struct BPTreeNode {
    bool is_leaf;
    int num_keys;
    char *keys[MAX_KEYS + 1]; // +1 para operações temporárias
    struct BPTreeNode *children[ORDER + 1];
    Stats *values[MAX_KEYS + 1]; // usado apenas em folhas
    struct BPTreeNode *parent;
    struct BPTreeNode *next; // ligação entre folhas
} BPTreeNode;

// Estrutura principal da árvore
typedef struct BPTree {
    BPTreeNode *root;
} BPTree;

// API pública
BPTree *bptree_create(void);
void bptree_free(BPTree *tree);
void bptree_insert(BPTree *tree, const char *key, Stats value);
bool bptree_update_add(BPTree *tree, const char *key, Stats new_value);
bool bptree_find(BPTree *tree, const char *key, Stats *out_stats);
bool bptree_save_to_file(BPTree *tree, const char *filename);

#endif