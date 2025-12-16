#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/bptree.h"

#define ORDER BPTREE_ORDER
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS ((ORDER/2) - 1)

typedef struct BPTreeNode {
    bool is_leaf;
    int num_keys;
    char *keys[MAX_KEYS + 1]; // +1 for temporary splits
    struct BPTreeNode *children[ORDER + 1];
    Stats *values[MAX_KEYS + 1]; // used only in leaves
    struct BPTreeNode *parent;
    struct BPTreeNode *next; // leaf linkage
} BPTreeNode;

struct BPTree {
    BPTreeNode *root;
};

static BPTreeNode *node_create(bool leaf) {
    BPTreeNode *n = calloc(1, sizeof(BPTreeNode));
    if (!n) return NULL;
    n->is_leaf = leaf;
    n->num_keys = 0;
    n->parent = NULL;
    n->next = NULL;
    return n;
}

/* Declaração implícita para strdup (evitar erro de compilação) */
static char *xstrdup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (!p) return NULL;
    memcpy(p, s, n);
    return p;
}

BPTree *bptree_create(void) {
    BPTree *t = malloc(sizeof(BPTree));
    if (!t) return NULL;
    t->root = node_create(true);
    return t;
}

static void free_node_recursive(BPTreeNode *n) {
    if (!n) return;
    if (!n->is_leaf) {
        for (int i = 0; i <= n->num_keys; ++i) {
            free_node_recursive(n->children[i]);
        }
    } else {
        for (int i = 0; i < n->num_keys; ++i) {
            free(n->keys[i]);
            free(n->values[i]);
        }
    }
    free(n);
}

void bptree_free(BPTree *tree) {
    if (!tree) return;
    free_node_recursive(tree->root);
    free(tree);
}

static BPTreeNode *find_leaf(BPTreeNode *root, const char *key) {
    BPTreeNode *n = root;
    while (n && !n->is_leaf) {
        int i = 0;
        while (i < n->num_keys && strcmp(key, n->keys[i]) >= 0) i++;
        n = n->children[i];
    }
    return n;
}

bool bptree_find(BPTree *tree, const char *key, Stats *out_stats) {
    if (!tree || !tree->root) return false;
    BPTreeNode *leaf = find_leaf(tree->root, key);
    if (!leaf) return false;
    for (int i = 0; i < leaf->num_keys; ++i) {
        if (strcmp(leaf->keys[i], key) == 0) {
            if (out_stats) *out_stats = *leaf->values[i];
            return true;
        }
    }
    return false;
}

static void insert_into_leaf(BPTreeNode *leaf, const char *key, Stats value) {
    int i = 0;
    while (i < leaf->num_keys && strcmp(leaf->keys[i], key) < 0) i++;
    if (i < leaf->num_keys && strcmp(leaf->keys[i], key) == 0) {
        // update
        *leaf->values[i] = value;
        return;
    }
    for (int j = leaf->num_keys; j > i; --j) {
        leaf->keys[j] = leaf->keys[j-1];
        leaf->values[j] = leaf->values[j-1];
    }
    leaf->keys[i] = xstrdup(key);
    leaf->values[i] = malloc(sizeof(Stats));
    *leaf->values[i] = value;
    leaf->num_keys++;
}

static void split_and_insert_leaf(BPTree *tree, BPTreeNode *leaf, const char *key, Stats value) {
    // temporary arrays
    char *temp_keys[MAX_KEYS + 1];
    Stats *temp_vals[MAX_KEYS + 1];
    int i = 0, j;
    while (i < leaf->num_keys && strcmp(leaf->keys[i], key) < 0) i++;
    // copy and insert
    for (j = 0; j < i; ++j) {
        temp_keys[j] = leaf->keys[j];
        temp_vals[j] = leaf->values[j];
    }
    temp_keys[i] = xstrdup(key);
    temp_vals[i] = malloc(sizeof(Stats));
    *temp_vals[i] = value;
    for (j = i; j < leaf->num_keys; ++j) {
        temp_keys[j+1] = leaf->keys[j];
        temp_vals[j+1] = leaf->values[j];
    }
    int split = (MAX_KEYS + 1) / 2;
    leaf->num_keys = 0;
    for (j = 0; j < split; ++j) {
        leaf->keys[j] = temp_keys[j];
        leaf->values[j] = temp_vals[j];
        leaf->num_keys++;
    }
    BPTreeNode *new_leaf = node_create(true);
    for (j = split; j < MAX_KEYS + 1; ++j) {
        new_leaf->keys[new_leaf->num_keys] = temp_keys[j];
        new_leaf->values[new_leaf->num_keys] = temp_vals[j];
        new_leaf->num_keys++;
    }
    new_leaf->next = leaf->next;
    leaf->next = new_leaf;
    new_leaf->parent = leaf->parent;

    // promote first key of new_leaf to parent
    char *promote = xstrdup(new_leaf->keys[0]);

    // insert into parent
    // if leaf was root
    if (leaf->parent == NULL) {
        BPTreeNode *new_root = node_create(false);
        new_root->keys[0] = promote;
        new_root->children[0] = leaf;
        new_root->children[1] = new_leaf;
        new_root->num_keys = 1;
        leaf->parent = new_root;
        new_leaf->parent = new_root;
        tree->root = new_root;
        return;
    }

    // otherwise insert promote into parent
    BPTreeNode *parent = leaf->parent;
    // find insertion index
    int idx = 0;
    while (idx < parent->num_keys && strcmp(promote, parent->keys[idx]) >= 0) idx++;
    // shift
    for (j = parent->num_keys; j > idx; --j) {
        parent->keys[j] = parent->keys[j-1];
        parent->children[j+1] = parent->children[j];
    }
    parent->keys[idx] = promote;
    parent->children[idx+1] = new_leaf;
    parent->num_keys++;
    new_leaf->parent = parent;

    // split internal nodes if necessary
    while (parent->num_keys > MAX_KEYS) {
        // split parent
        int mid = (MAX_KEYS + 1) / 2;
        BPTreeNode *new_internal = node_create(false);
        // move keys and children
        int k;
        for (k = mid + 1; k <= parent->num_keys; ++k) {
            new_internal->children[new_internal->num_keys] = parent->children[k];
            if (new_internal->children[new_internal->num_keys])
                new_internal->children[new_internal->num_keys]->parent = new_internal;
            new_internal->keys[new_internal->num_keys] = parent->keys[k-1];
            new_internal->num_keys++;
        }
        char *upkey = parent->keys[mid];
        parent->num_keys = mid;

        new_internal->parent = parent->parent;

        if (parent->parent == NULL) {
            BPTreeNode *new_root = node_create(false);
            new_root->keys[0] = upkey;
            new_root->children[0] = parent;
            new_root->children[1] = new_internal;
            new_root->num_keys = 1;
            parent->parent = new_root;
            new_internal->parent = new_root;
            tree->root = new_root;
            break;
        } else {
            BPTreeNode *gp = parent->parent;
            int pos = 0;
            while (pos < gp->num_keys && strcmp(upkey, gp->keys[pos]) >= 0) pos++;
            for (k = gp->num_keys; k > pos; --k) {
                gp->keys[k] = gp->keys[k-1];
                gp->children[k+1] = gp->children[k];
            }
            gp->keys[pos] = upkey;
            gp->children[pos+1] = new_internal;
            gp->num_keys++;
            new_internal->parent = gp;
            parent = gp;
            // continue while if gp overflows
        }
    }
}

void bptree_insert(BPTree *tree, const char *key, Stats value) {
    if (!tree || !key) return;
    BPTreeNode *root = tree->root;
    if (!root) {
        tree->root = node_create(true);
        root = tree->root;
    }
    BPTreeNode *leaf = find_leaf(root, key);
    if (!leaf) leaf = tree->root;
    // check if key exists in leaf
    for (int i = 0; i < leaf->num_keys; ++i) {
        if (strcmp(leaf->keys[i], key) == 0) {
            *leaf->values[i] = value; // update
            return;
        }
    }
    if (leaf->num_keys < MAX_KEYS) {
        insert_into_leaf(leaf, key, value);
    } else {
        split_and_insert_leaf(tree, leaf, key, value);
    }
}

/* Update existing record by adding new values to current ones */
bool bptree_update_add(BPTree *tree, const char *key, Stats new_value) {
    if (!tree || !key) return false;
    
    BPTreeNode *root = tree->root;
    if (!root) return false;
    
    BPTreeNode *leaf = find_leaf(root, key);
    if (!leaf) return false;
    
    for (int i = 0; i < leaf->num_keys; ++i) {
        if (strcmp(leaf->keys[i], key) == 0) {
            // Encontrou o jogador - SOMAR os valores
            leaf->values[i]->vida = new_value.vida; // Vida atual (não soma)
            leaf->values[i]->cont_vitorias += new_value.cont_vitorias;
            leaf->values[i]->distancia_percorrida += new_value.distancia_percorrida;
            leaf->values[i]->cont_dano += new_value.cont_dano;
            return true;
        }
    }
    return false; // Chave não encontrada
}

// ... no final da função bptree_save_to_file:
bool bptree_save_to_file(BPTree *tree, const char *filename) {
    if (!tree || !filename) return false;
    FILE *f = fopen(filename, "w");
    if (!f) return false;
    // find leftmost leaf
    BPTreeNode *n = tree->root;
    while (n && !n->is_leaf) n = n->children[0];
    while (n) {
        for (int i = 0; i < n->num_keys; ++i) {
            // Atualizado para refletir que o terceiro campo agora é distancia_percorrida
            fprintf(f, "%s: vida=%d, vitorias=%d, distancia=%d, dano=%d\n",
                    n->keys[i], n->values[i]->vida, n->values[i]->cont_vitorias,
                    n->values[i]->distancia_percorrida, n->values[i]->cont_dano);
        }
        n = n->next;
    }
    fclose(f);
    return true;
}