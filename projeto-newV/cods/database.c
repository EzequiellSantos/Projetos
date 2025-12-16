#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/bptree.h"
#include "../includes/database.h"

#define DB_FILENAME "data.txt"

// Função para extrair nome e stats de uma linha do arquivo
static bool parse_linha_arquivo(const char *linha, char *nome, Stats *stats) {
    // Formato: "nome: vida=X, vitorias=Y, distancia=Z, dano=W"
    return (sscanf(linha, "%49[^:]: vida=%d, vitorias=%d, distancia=%d, dano=%d",
                   nome, &stats->vida, &stats->cont_vitorias,
                   &stats->distancia_percorrida, &stats->cont_dano) == 5);
}

// Carregar dados do arquivo para a árvore
void carregar_dados_disco(BPTree *tree) {
    FILE *file = fopen(DB_FILENAME, "r");
    if (!file) return; // Arquivo não existe ainda
    
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        // Remover newline
        linha[strcspn(linha, "\n")] = 0;
        
        char nome[50];
        Stats stats;
        
        if (parse_linha_arquivo(linha, nome, &stats)) {
            // Inserir na árvore (será substituído se já existir)
            bptree_insert(tree, nome, stats);
        }
    }
    
    fclose(file);
}

// Salvar árvore para disco
void salvar_dados_disco(BPTree *tree) {
    bptree_save_to_file(tree, DB_FILENAME);
}

// Função para inserir ou atualizar estatísticas
void inserir_ou_atualizar_stats(BPTree *tree, const char *nome, Stats novas_stats) {
    Stats stats_existente;
    
    // Tenta encontrar estatísticas existentes
    if (bptree_find(tree, nome, &stats_existente)) {
        // Jogador existe - SOMAR os valores (exceto vida que é resetada a cada partida)
        stats_existente.cont_vitorias += novas_stats.cont_vitorias;
        stats_existente.distancia_percorrida += novas_stats.distancia_percorrida;
        stats_existente.cont_dano += novas_stats.cont_dano;
        
        // Atualizar na árvore
        bptree_insert(tree, nome, stats_existente);
    } else {
        // Jogador não existe - inserir novo
        bptree_insert(tree, nome, novas_stats);
    }
}