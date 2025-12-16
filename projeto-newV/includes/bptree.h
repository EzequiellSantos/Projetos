#ifndef BPTREE_H
#define BPTREE_H

#include <stdbool.h>

#define BPTREE_ORDER 4

typedef struct Stats {
    int vida;
    int cont_vitorias;
    int distancia_percorrida; // Renomeado de cont_mov para distancia_percorrida
    int cont_dano;
} Stats;

typedef struct BPTree BPTree;

BPTree *bptree_create(void);
void bptree_free(BPTree *tree);

/* Insert or update a key (string). If key exists, replace the Stats.
   Memory for key is copied. */
void bptree_insert(BPTree *tree, const char *key, Stats value);

/* Update existing record by adding new values to current ones */
bool bptree_update_add(BPTree *tree, const char *key, Stats new_value);

/* Find record by key; returns true if found and fills out_stats */
bool bptree_find(BPTree *tree, const char *key, Stats *out_stats);

/* Save all records in-order (leaves) to text file in a human readable format */
bool bptree_save_to_file(BPTree *tree, const char *filename);

#endif