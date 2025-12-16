[file name]: bptree_visual.c
[file content begin]
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/bptree.h"
#include "../includes/ranking.h"

// Estrutura para coordenadas de desenho
typedef struct {
    int x;
    int y;
    int width;
    int height;
} DrawCoords;

// Estrutura para nó na visualização
typedef struct {
    BPTreeNode *node;
    DrawCoords coords;
    struct VisualNode *parent;
    int child_index;
} VisualNode;

// Estrutura para gerenciar a visualização
typedef struct {
    VisualNode **nodes;
    int count;
    int capacity;
    int max_depth;
    int screen_width;
    int screen_height;
} TreeVisualizer;

// Funções auxiliares para a visualização
static TreeVisualizer* visualizer_create(int screen_width, int screen_height) {
    TreeVisualizer *tv = malloc(sizeof(TreeVisualizer));
    if (!tv) return NULL;
    
    tv->capacity = 50;
    tv->count = 0;
    tv->max_depth = 0;
    tv->screen_width = screen_width;
    tv->screen_height = screen_height;
    tv->nodes = malloc(tv->capacity * sizeof(VisualNode*));
    
    return tv;
}

static void visualizer_add_node(TreeVisualizer *tv, VisualNode *node) {
    if (tv->count >= tv->capacity) {
        tv->capacity *= 2;
        tv->nodes = realloc(tv->nodes, tv->capacity * sizeof(VisualNode*));
    }
    tv->nodes[tv->count++] = node;
}

static void visualizer_free(TreeVisualizer *tv) {
    if (!tv) return;
    for (int i = 0; i < tv->count; i++) {
        free(tv->nodes[i]);
    }
    free(tv->nodes);
    free(tv);
}

// Calcular profundidade da árvore
static int calculate_tree_depth(BPTreeNode *node, int current_depth) {
    if (!node) return current_depth;
    if (node->is_leaf) return current_depth;
    
    int max_depth = current_depth;
    for (int i = 0; i <= node->num_keys; i++) {
        if (node->children[i]) {
            int depth = calculate_tree_depth(node->children[i], current_depth + 1);
            if (depth > max_depth) max_depth = depth;
        }
    }
    return max_depth;
}

// Coletar nós para visualização
static void collect_nodes(BPTreeNode *node, VisualNode *parent, int child_idx, 
                          int level, TreeVisualizer *tv, int x, int y, int x_spacing) {
    if (!node) return;
    
    VisualNode *vn = malloc(sizeof(VisualNode));
    vn->node = node;
    vn->parent = parent;
    vn->child_index = child_idx;
    
    // Calcular largura baseada no número de chaves
    int node_width = 15 + (node->num_keys * 8);
    int node_height = 3 + (node->num_keys * 1);
    
    vn->coords.x = x;
    vn->coords.y = y;
    vn->coords.width = node_width;
    vn->coords.height = node_height;
    
    visualizer_add_node(tv, vn);
    
    if (level > tv->max_depth) tv->max_depth = level;
    
    // Para nós internos, processar filhos
    if (!node->is_leaf) {
        int child_y = y + node_height + 3;
        int total_children = node->num_keys + 1;
        int total_child_width = (total_children - 1) * x_spacing;
        int start_x = x - (total_child_width / 2);
        
        for (int i = 0; i <= node->num_keys; i++) {
            if (node->children[i]) {
                int child_x = start_x + (i * x_spacing);
                collect_nodes(node->children[i], vn, i, level + 1, tv, 
                            child_x, child_y, x_spacing / (node->num_keys + 1));
            }
        }
    }
}

// Desenhar um nó da árvore
static void draw_tree_node(VisualNode *vn, RankingCriterio criterio, int ranking_position) {
    BPTreeNode *node = vn->node;
    DrawCoords *c = &vn->coords;
    
    // Determinar cor baseado na posição no ranking (se for folha)
    int color_pair = 2; // Azul padrão para nós internos
    
    if (node->is_leaf && ranking_position >= 0) {
        if (ranking_position == 0) color_pair = 3; // Ouro
        else if (ranking_position == 1) color_pair = 5; // Prata
        else if (ranking_position == 2) color_pair = 1; // Bronze
        else color_pair = 4; // Verde para outros
    } else if (!node->is_leaf) {
        color_pair = 5; // Ciano para nós internos
    }
    
    // Desenhar borda do nó
    attron(COLOR_PAIR(color_pair));
    
    // Canto superior esquerdo
    mvaddch(c->y, c->x, '┌');
    
    // Linha superior
    for (int i = 1; i < c->width - 1; i++) {
        mvaddch(c->y, c->x + i, '─');
    }
    
    // Canto superior direito
    mvaddch(c->y, c->x + c->width - 1, '┐');
    
    // Linhas laterais e conteúdo
    for (int row = 1; row < c->height - 1; row++) {
        mvaddch(c->y + row, c->x, '│');
        
        // Conteúdo do nó
        if (row == 1) {
            // Tipo do nó
            char node_type[20];
            snprintf(node_type, 20, "%s", node->is_leaf ? "FOLHA" : "INTERNO");
            int text_x = c->x + (c->width - strlen(node_type)) / 2;
            attron(A_BOLD);
            mvprintw(c->y + row, text_x, "%s", node_type);
            attroff(A_BOLD);
        } else if (row >= 2 && row - 2 < node->num_keys) {
            int key_idx = row - 2;
            char display_key[40];
            
            if (node->is_leaf && node->values[key_idx]) {
                // Para folhas: mostrar nome e estatística relevante
                int stat_value;
                switch (criterio) {
                    case RANKING_DANO: stat_value = node->values[key_idx]->cont_dano; break;
                    case RANKING_VITORIAS: stat_value = node->values[key_idx]->cont_vitorias; break;
                    case RANKING_DISTANCIA: stat_value = node->values[key_idx]->distancia_percorrida; break;
                    default: stat_value = 0;
                }
                snprintf(display_key, 40, "%-10s: %d", 
                        node->keys[key_idx], stat_value);
            } else {
                // Para nós internos: mostrar apenas a chave
                snprintf(display_key, 40, "%-15s", node->keys[key_idx]);
            }
            
            int text_x = c->x + (c->width - strlen(display_key)) / 2;
            mvprintw(c->y + row, text_x, "%s", display_key);
        }
        
        mvaddch(c->y + row, c->x + c->width - 1, '│');
    }
    
    // Linha inferior
    mvaddch(c->y + c->height - 1, c->x, '└');
    for (int i = 1; i < c->width - 1; i++) {
        mvaddch(c->y + c->height - 1, c->x + i, '─');
    }
    mvaddch(c->y + c->height - 1, c->x + c->width - 1, '┘');
    
    // Número de chaves no canto inferior direito
    char key_count[10];
    snprintf(key_count, 10, "K:%d", node->num_keys);
    mvprintw(c->y + c->height - 1, c->x + c->width - strlen(key_count) - 1, "%s", key_count);
    
    attroff(COLOR_PAIR(color_pair));
}

// Desenhar conexões entre nós
static void draw_tree_connections(TreeVisualizer *tv) {
    attron(COLOR_PAIR(5));
    
    for (int i = 0; i < tv->count; i++) {
        VisualNode *child = tv->nodes[i];
        if (child->parent) {
            VisualNode *parent = child->parent;
            
            int parent_bottom = parent->coords.y + parent->coords.height;
            int child_top = child->coords.y;
            int parent_center = parent->coords.x + (parent->coords.width / 2);
            int child_center = child->coords.x + (child->coords.width / 2);
            
            // Desenhar linha vertical do pai
            for (int y = parent_bottom; y < parent_bottom + 1; y++) {
                if (y >= 0 && y < tv->screen_height) {
                    mvaddch(y, parent_center, '│');
                }
            }
            
            // Desenhar linha horizontal
            int connect_y = parent_bottom + 1;
            int start_x = parent_center < child_center ? parent_center : child_center;
            int end_x = parent_center < child_center ? child_center : parent_center;
            
            for (int x = start_x; x <= end_x; x++) {
                if (x >= 0 && x < tv->screen_width && connect_y >= 0 && connect_y < tv->screen_height) {
                    if (x == parent_center) {
                        mvaddch(connect_y, x, '┬');
                    } else if (x == child_center) {
                        mvaddch(connect_y, x, '┴');
                    } else {
                        mvaddch(connect_y, x, '─');
                    }
                }
            }
            
            // Desenhar linha vertical do filho
            for (int y = connect_y + 1; y < child_top; y++) {
                if (y >= 0 && y < tv->screen_height && child_center >= 0 && child_center < tv->screen_width) {
                    mvaddch(y, child_center, '│');
                }
            }
        }
    }
    
    attroff(COLOR_PAIR(5));
}

// Encontrar ranking position para um nome
static int find_ranking_position(const char *name, RankingEntry *ranking, int count, RankingCriterio criterio) {
    for (int i = 0; i < count; i++) {
        if (strcmp(ranking[i].nome, name) == 0) {
            return i; // Retorna a posição no ranking
        }
    }
    return -1;
}

// Função principal para mostrar a árvore B+ real
void mostrar_arvore_bplus_real(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio) {
    if (!tree || !tree->root) {
        // Mostrar mensagem se não houver árvore
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(10, 20, "⚠️  Nenhuma árvore B+ carregada!");
        mvprintw(11, 15, "Jogue algumas partidas para gerar estatísticas");
        attroff(A_BOLD | COLOR_PAIR(3));
        return;
    }
    
    // Calcular dimensões da tela
    int screen_height = getmaxy(stdscr);
    int screen_width = getmaxx(stdscr);
    
    // Calcular profundidade da árvore
    int tree_depth = calculate_tree_depth(tree->root, 0);
    
    // Criar visualizador
    TreeVisualizer *tv = visualizer_create(screen_width, screen_height);
    
    // Calcular espaçamento baseado na profundidade
    int x_spacing = screen_width / (int)pow(2, tree_depth);
    int start_y = 5;
    int start_x = screen_width / 2;
    
    // Coletar todos os nós para desenho
    collect_nodes(tree->root, NULL, -1, 0, tv, start_x, start_y, x_spacing);
    
    // Desenhar título e informações
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(1, 2, "╔══════════════════════════════════════════════════════════════════════════════╗");
    mvprintw(2, 2, "║                     🌳 VISUALIZAÇÃO DA ÁRVORE B+ REAL 🌳                     ║");
    mvprintw(3, 2, "╚══════════════════════════════════════════════════════════════════════════════╝");
    
    // Informações sobre a árvore
    attron(COLOR_PAIR(3));
    mvprintw(5, 2, "📊 Estatísticas da Árvore:");
    mvprintw(6, 4, "• Profundidade: %d níveis", tree_depth + 1);
    mvprintw(7, 4, "• Total de nós na visualização: %d", tv->count);
    mvprintw(8, 4, "• Ordem da árvore: %d", ORDER);
    mvprintw(9, 4, "• Critério atual: %s", 
            criterio == RANKING_DANO ? "Maior Dano" :
            criterio == RANKING_VITORIAS ? "Mais Vitórias" : "Maior Distância");
    
    // Legenda
    attron(COLOR_PAIR(5));
    mvprintw(screen_height - 8, 2, "🎨 Legenda de Cores:");
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(screen_height - 7, 4, "🥇 Dourado - 1º lugar no ranking");
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(screen_height - 6, 4, "🥈 Prata - 2º lugar no ranking");
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(screen_height - 5, 4, "🥉 Bronze - 3º lugar no ranking");
    attron(COLOR_PAIR(4));
    mvprintw(screen_height - 4, 4, "🟢 Verde - Outras posições no ranking");
    attron(COLOR_PAIR(5));
    mvprintw(screen_height - 3, 4, "🔵 Ciano - Nós internos da árvore");
    
    // Instruções
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(screen_height - 1, 2, "ESC: Voltar | ▲/▼: Scroll vertical | ◄/►: Scroll horizontal");
    
    // Desenhar conexões primeiro (para ficarem atrás dos nós)
    draw_tree_connections(tv);
    
    // Desenhar todos os nós
    for (int i = 0; i < tv->count; i++) {
        VisualNode *vn = tv->nodes[i];
        
        // Verificar se é uma folha com dados de jogador
        int ranking_position = -1;
        if (vn->node->is_leaf && vn->node->num_keys > 0 && ranking_count > 0) {
            // Para cada chave na folha, encontrar sua posição no ranking
            for (int k = 0; k < vn->node->num_keys; k++) {
                if (vn->node->keys[k]) {
                    ranking_position = find_ranking_position(vn->node->keys[k], 
                                                           ranking, ranking_count, criterio);
                    break; // Usar a primeira chave como referência
                }
            }
        }
        
        draw_tree_node(vn, criterio, ranking_position);
    }
    
    // Desenhar explicação da estrutura B+
    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(screen_height - 12, screen_width - 40, "📚 Estrutura B+:");
    attroff(A_BOLD);
    attron(COLOR_PAIR(4));
    mvprintw(screen_height - 11, screen_width - 40, "• Nós internos: Chaves de roteamento");
    mvprintw(screen_height - 10, screen_width - 40, "• Folhas: Dados ordenados + ponteiros");
    mvprintw(screen_height - 9, screen_width - 40, "• Todas folhas no mesmo nível");
    mvprintw(screen_height - 8, screen_width - 40, "• K: Número de chaves no nó");
    
    // Liberar memória do visualizador
    visualizer_free(tv);
}

// Nova função para mostrar menu de visualização da árvore
void mostrar_menu_arvore_ranking(BPTree *tree) {
    if (!tree) return;
    
    // Carregar dados para ranking
    RankingEntry *ranking_array = NULL;
    int count = 0;
    bool dados_carregados = ler_dados_arquivo("data.txt", &ranking_array, &count);
    
    if (!dados_carregados || count == 0) {
        // Se não houver dados, mostrar mensagem
        clear();
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(10, 20, "📭 Nenhum dado de ranking disponível!");
        mvprintw(11, 15, "Jogue algumas partidas para gerar estatísticas");
        mvprintw(13, 20, "Pressione qualquer tecla para voltar...");
        attroff(A_BOLD | COLOR_PAIR(3));
        refresh();
        getch();
        return;
    }
    
    RankingCriterio criterio_atual = RANKING_DANO;
    ordenar_ranking(ranking_array, count, criterio_atual);
    
    int sair = 0;
    int offset_y = 0;
    int offset_x = 0;
    
    while (!sair) {
        clear();
        
        // Mostrar a árvore B+ real
        mostrar_arvore_bplus_real(tree, ranking_array, count, criterio_atual);
        
        // Menu de controle na parte superior
        attron(A_BOLD | COLOR_PAIR(5));
        mvprintw(0, 2, "┌──────────────────────────────────────────────────────────────┐");
        mvprintw(1, 2, "│                     CONTROLES DA ÁRVORE B+                   │");
        mvprintw(2, 2, "├──────────────────────────────────────────────────────────────┤");
        
        // Opções de critério
        if (criterio_atual == RANKING_DANO) {
            attron(COLOR_PAIR(1) | A_REVERSE);
        } else {
            attron(COLOR_PAIR(1));
        }
        mvprintw(3, 4, " [1] Por Dano ");
        
        if (criterio_atual == RANKING_VITORIAS) {
            attron(COLOR_PAIR(4) | A_REVERSE);
        } else {
            attron(COLOR_PAIR(4));
        }
        mvprintw(3, 20, " [2] Por Vitórias ");
        
        if (criterio_atual == RANKING_DISTANCIA) {
            attron(COLOR_PAIR(2) | A_REVERSE);
        } else {
            attron(COLOR_PAIR(2));
        }
        mvprintw(3, 40, " [3] Por Distância ");
        
        attron(COLOR_PAIR(3));
        mvprintw(3, 60, " [ESC] Voltar ");
        
        mvprintw(4, 2, "└──────────────────────────────────────────────────────────────┘");
        
        refresh();
        
        // Processar input
        int ch = getch();
        switch (ch) {
            case '1':
                criterio_atual = RANKING_DANO;
                ordenar_ranking(ranking_array, count, criterio_atual);
                break;
                
            case '2':
                criterio_atual = RANKING_VITORIAS;
                ordenar_ranking(ranking_array, count, criterio_atual);
                break;
                
            case '3':
                criterio_atual = RANKING_DISTANCIA;
                ordenar_ranking(ranking_array, count, criterio_atual);
                break;
                
            case KEY_UP:
                offset_y -= 2;
                break;
                
            case KEY_DOWN:
                offset_y += 2;
                break;
                
            case KEY_LEFT:
                offset_x -= 2;
                break;
                
            case KEY_RIGHT:
                offset_x += 2;
                break;
                
            case 27: // ESC
                sair = 1;
                break;
        }
    }
    
    // Liberar memória
    liberar_array_ranking(ranking_array);
}
[file content end]

[file name]: ranking.h (modificação)
[file content begin]
#ifndef RANKING_H
#define RANKING_H

#include <stdbool.h>
#include "bptree.h"  // Adicionar include para BPTree

// ... código existente ...

// Adicionar no final do arquivo:
// Função para mostrar a árvore B+ real
void mostrar_arvore_bplus_real(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio);

// Função para mostrar menu da árvore de ranking
void mostrar_menu_arvore_ranking(BPTree *tree);

#endif
[file content end]

[file name]: main.c (modificação para incluir opção de árvore)
[file content begin]
// No switch case da opção de ranking, modificar para:
case 2: // Ver Ranking
    clear();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    
    // Carregar dados do ranking
    RankingEntry *ranking_array = NULL;
    int count = 0;
    bool dados_carregados = ler_dados_arquivo("data.txt", &ranking_array, &count);
    
    if (dados_carregados && count > 0) {
        // Menu para escolher entre tabela e árvore
        int opcao_visualizacao = 0;
        int sair_ranking = 0;
        
        while (!sair_ranking) {
            clear();
            mvprintw(2, 2, "=== VISUALIZAÇÃO DO RANKING ===");
            mvprintw(4, 4, "1. Ver em Tabela");
            mvprintw(5, 4, "2. Ver Árvore B+ (Simulada)");
            mvprintw(6, 4, "3. Ver Árvore B+ Real");
            mvprintw(7, 4, "4. Voltar ao Menu");
            
            mvprintw(4 + opcao_visualizacao, 3, ">");
            
            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    opcao_visualizacao = (opcao_visualizacao - 1 + 4) % 4;
                    break;
                case KEY_DOWN:
                    opcao_visualizacao = (opcao_visualizacao + 1) % 4;
                    break;
                case '\n':
                case KEY_ENTER:
                    if (opcao_visualizacao == 0) {
                        mostrar_tela_ranking();  // Tabela tradicional
                    } else if (opcao_visualizacao == 1) {
                        // Mostrar árvore B+ simulada
                        mostrar_arvore_bplus(ranking_array, count, RANKING_DANO);
                    } else if (opcao_visualizacao == 2) {
                        // Mostrar árvore B+ real
                        // Criar árvore temporária para visualização
                        BPTree *temp_tree = bptree_create();
                        
                        // Carregar dados do arquivo para a árvore
                        for (int i = 0; i < count; i++) {
                            Stats stats = {
                                ranking_array[i].stats.vida,
                                ranking_array[i].stats.cont_vitorias,
                                ranking_array[i].stats.distancia_percorrida,
                                ranking_array[i].stats.cont_dano
                            };
                            bptree_insert(temp_tree, ranking_array[i].nome, stats);
                        }
                        
                        mostrar_menu_arvore_ranking(temp_tree);
                        bptree_free(temp_tree);
                    } else {
                        sair_ranking = 1;
                    }
                    break;
                case '1':
                    mostrar_tela_ranking();
                    break;
                case '2':
                    mostrar_arvore_bplus(ranking_array, count, RANKING_DANO);
                    break;
                case '3':
                    // Mostrar árvore B+ real
                    BPTree *temp_tree = bptree_create();
                    for (int i = 0; i < count; i++) {
                        Stats stats = {
                            ranking_array[i].stats.vida,
                            ranking_array[i].stats.cont_vitorias,
                            ranking_array[i].stats.distancia_percorrida,
                            ranking_array[i].stats.cont_dano
                        };
                        bptree_insert(temp_tree, ranking_array[i].nome, stats);
                    }
                    mostrar_menu_arvore_ranking(temp_tree);
                    bptree_free(temp_tree);
                    break;
                case '4':
                case 27: // ESC
                    sair_ranking = 1;
                    break;
            }
        }
        
        liberar_array_ranking(ranking_array);
    } else {
        // Se não houver dados, mostrar mensagem
        mostrar_tela_ranking();
    }
    
    clear();
    break;
[file content end]

[file name]: Makefile (adição do novo arquivo)
[file content begin]
# No Makefile, adicionar bptree_visual.c à lista de arquivos:
SRC = main.c menu.c mapa.c bomb.c bomb_types.c game_over.c player.c auth.c auth_menu.c stats.c database.c ranking.c bptree.c bptree_visual.c

# E também adicionar à lista de objetos:
OBJ = $(SRC:.c=.o)
[file content end]