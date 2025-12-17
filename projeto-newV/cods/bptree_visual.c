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

// Estrutura para nó na visualização - usando forward declaration
typedef struct VisualNode VisualNode;

struct VisualNode {
    BPTreeNode *node;
    DrawCoords coords;
    VisualNode *parent;  // Agora usa o tipo correto
    int child_index;
};

// Estrutura para gerenciar a visualização
typedef struct {
    VisualNode **nodes;
    int count;
    int capacity;
    int max_depth;
    int screen_width;
    int screen_height;
} TreeVisualizer;

// DECLARAÇÕES DE FUNÇÕES (tudo no início do arquivo)
static TreeVisualizer* visualizer_create(int screen_width, int screen_height);
static void visualizer_add_node(TreeVisualizer *tv, VisualNode *node);
static void visualizer_free(TreeVisualizer *tv);
static int calculate_tree_depth(BPTreeNode *node, int current_depth);
static int calculate_node_width(BPTreeNode *node);
static int calculate_node_height(BPTreeNode *node);
static void draw_char(int y, int x, int ch);
static void draw_tree_node(VisualNode *vn, RankingCriterio criterio, int ranking_position);
static void draw_tree_connections(TreeVisualizer *tv);
static int find_ranking_position(const char *name, RankingEntry *ranking, int count, RankingCriterio criterio);
static void collect_nodes(BPTreeNode *node, VisualNode *parent, int child_idx, 
                          int level, TreeVisualizer *tv, int x, int y, int x_spacing, 
                          int max_screen_width);
static void layout_tree_nodes(BPTreeNode *node, VisualNode *parent, int child_idx,
                             int level, TreeVisualizer *tv, int screen_width, int screen_height);
static bool tree_fits_screen(TreeVisualizer *tv, int screen_width, int screen_height);
static int contar_nos_arvore(BPTreeNode *node);
static int contar_folhas(BPTreeNode *node);
void mostrar_arvore_bplus_real(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio);
void mostrar_arvore_com_scroll(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio);
void mostrar_arvore_simplificada(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio);
void mostrar_menu_arvore_ranking(BPTree *tree);

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

// Função auxiliar para calcular a largura necessária para um nó
static int calculate_node_width(BPTreeNode *node) {
    if (!node) return 20;
    
    // Calcular largura baseada no conteúdo
    int max_key_len = 0;
    for (int i = 0; i < node->num_keys; i++) {
        if (node->keys[i]) {
            int len = strlen(node->keys[i]);
            if (len > max_key_len) max_key_len = len;
        }
    }
    
    // Largura mínima para bordas e espaçamento
    int min_width = 15;
    int calculated_width = 15 + (max_key_len * 2);
    
    return (calculated_width > min_width) ? calculated_width : min_width;
}

// Função auxiliar para calcular a altura necessária para um nó
static int calculate_node_height(BPTreeNode *node) {
    if (!node) return 4;
    return 3 + node->num_keys; // Linha do título + 1 linha por chave
}

// Coletar nós para visualização COM LAYOUT MELHORADO
static void collect_nodes(BPTreeNode *node, VisualNode *parent, int child_idx, 
                          int level, TreeVisualizer *tv, int x, int y, int x_spacing, 
                          int max_screen_width) {
    if (!node) return;
    
    VisualNode *vn = malloc(sizeof(VisualNode));
    vn->node = node;
    vn->parent = parent;
    vn->child_index = child_idx;
    
    // Calcular dimensões do nó
    int node_width = calculate_node_width(node);
    int node_height = calculate_node_height(node);
    
    // Ajustar posição X para não sair da tela
    int adjusted_x = x;
    if (adjusted_x < 5) adjusted_x = 5;
    if (adjusted_x + node_width > max_screen_width - 5) {
        adjusted_x = max_screen_width - node_width - 5;
    }
    
    vn->coords.x = adjusted_x;
    vn->coords.y = y;
    vn->coords.width = node_width;
    vn->coords.height = node_height;
    
    visualizer_add_node(tv, vn);
    
    if (level > tv->max_depth) tv->max_depth = level;
    
    // Para nós internos, processar filhos
    if (!node->is_leaf) {
        int child_y = y + node_height + 3;
        
        // Calcular espaçamento dinâmico baseado no número de filhos e largura da tela
        int total_children = node->num_keys + 1;
        
        // Se for a raiz com poucos filhos, usar espaçamento maior
        if (level == 0 && total_children <= 3) {
            x_spacing = max_screen_width / (total_children + 1);
        }
        
        int total_child_width = (total_children - 1) * x_spacing;
        
        // Ajustar se for muito largo
        if (total_child_width > max_screen_width - 20) {
            x_spacing = (max_screen_width - 20) / (total_children - 1);
            total_child_width = (total_children - 1) * x_spacing;
        }
        
        int start_x = x - (total_child_width / 2);
        
        // Garantir que o start_x não fique fora da tela
        if (start_x < 5) {
            start_x = 5;
        } else if (start_x + total_child_width > max_screen_width - 5) {
            start_x = max_screen_width - total_child_width - 5;
        }
        
        // Calcular espaçamento para filhos (recursivamente reduzido)
        int child_x_spacing;
        if (level < 2) { // Níveis mais altos tem mais espaço
            child_x_spacing = x_spacing * 0.7;
        } else {
            child_x_spacing = x_spacing * 0.5;
        }
        
        // Mínimo de espaçamento
        if (child_x_spacing < 10) child_x_spacing = 10;
        
        for (int i = 0; i <= node->num_keys; i++) {
            if (node->children[i]) {
                int child_x = start_x + (i * x_spacing);
                
                // Ajustar posição do filho para caber na tela
                int child_node_width = calculate_node_width(node->children[i]);
                if (child_x < 5) child_x = 5;
                if (child_x + child_node_width > max_screen_width - 5) {
                    child_x = max_screen_width - child_node_width - 5;
                }
                
                collect_nodes(node->children[i], vn, i, level + 1, tv, 
                            child_x, child_y, child_x_spacing, max_screen_width);
            }
        }
    }
}

// Funções auxiliares para desenhar caracteres ASCII art
static void draw_char(int y, int x, int ch) {
    if (y >= 0 && y < LINES && x >= 0 && x < COLS) {
        mvaddch(y, x, ch);
    }
}

// Desenhar um nó da árvore - VERSÃO COM CORRESPONDÊNCIA DE CORES
static void draw_tree_node(VisualNode *vn, RankingCriterio criterio, int ranking_position) {
    BPTreeNode *node = vn->node;
    DrawCoords *c = &vn->coords;
    
    // Determinar cor baseado na posição no ranking (se for folha)
    // NOTA IMPORTANTE: As cores devem corresponder EXATAMENTE com a legenda!
    int color_pair = 2; // AZUL para nós internos (mas na verdade usamos 5 - CIANO)
    
    if (node->is_leaf && ranking_position >= 0) {
        if (ranking_position == 0) {
            color_pair = 3; // AMARELO/DOURADO para 1º lugar
        } else if (ranking_position == 1) {
            color_pair = 5; // CIANO/PRATA para 2º lugar
        } else if (ranking_position == 2) {
            color_pair = 1; // VERMELHO/BRONZE para 3º lugar
        } else {
            color_pair = 4; // VERDE para outras posições
        }
    } else if (!node->is_leaf) {
        // IMPORTANTE: Nós internos usam color pair 5 (CIANO) para ficar azul/ciano
        // Isso está correto para corresponder com "Nos internos - Cor Azul/Ciano" na legenda
        color_pair = 5; // CIANO para nós internos
    }
    
    // Desenhar borda do nó usando caracteres ASCII simples
    attron(COLOR_PAIR(color_pair));
    
    // Canto superior esquerdo
    draw_char(c->y, c->x, '+');
    
    // Linha superior
    for (int i = 1; i < c->width - 1; i++) {
        draw_char(c->y, c->x + i, '-');
    }
    
    // Canto superior direito
    draw_char(c->y, c->x + c->width - 1, '+');
    
    // Linhas laterais e conteúdo
    for (int row = 1; row < c->height - 1; row++) {
        draw_char(c->y + row, c->x, '|');
        
        // Conteúdo do nó
        if (row == 1) {
            // Tipo do nó
            char node_type[20];
            snprintf(node_type, 20, "%s", node->is_leaf ? "FOLHA" : "INTERNO");
            int text_x = c->x + (c->width - strlen(node_type)) / 2;
            
            // Aplicar atributos para o texto dentro do nó
            attron(A_BOLD);
            attron(COLOR_PAIR(color_pair));
            mvprintw(c->y + row, text_x, "%s", node_type);
            attroff(COLOR_PAIR(color_pair));
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
            
            // Aplicar cor para o texto dentro do nó
            attron(COLOR_PAIR(color_pair));
            mvprintw(c->y + row, text_x, "%s", display_key);
            attroff(COLOR_PAIR(color_pair));
        }
        
        draw_char(c->y + row, c->x + c->width - 1, '|');
    }
    
    // Linha inferior
    draw_char(c->y + c->height - 1, c->x, '+');
    for (int i = 1; i < c->width - 1; i++) {
        draw_char(c->y + c->height - 1, c->x + i, '-');
    }
    draw_char(c->y + c->height - 1, c->x + c->width - 1, '+');
    
    // Número de chaves no canto inferior direito
    char key_count[10];
    snprintf(key_count, 10, "K:%d", node->num_keys);
    
    // Aplicar cor para o texto do contador
    attron(COLOR_PAIR(color_pair));
    mvprintw(c->y + c->height - 1, c->x + c->width - strlen(key_count) - 1, "%s", key_count);
    attroff(COLOR_PAIR(color_pair));
    
    // IMPORTANTE: Desligar todos os atributos após desenhar o nó
    attroff(COLOR_PAIR(color_pair));
    attrset(A_NORMAL);
}

// Desenhar conexões entre nós usando caracteres ASCII
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
                draw_char(y, parent_center, '|');
            }
            
            // Desenhar linha horizontal
            int connect_y = parent_bottom + 1;
            int start_x = parent_center < child_center ? parent_center : child_center;
            int end_x = parent_center < child_center ? child_center : parent_center;
            
            for (int x = start_x; x <= end_x; x++) {
                if (x == parent_center) {
                    draw_char(connect_y, x, '+');
                } else if (x == child_center) {
                    draw_char(connect_y, x, '+');
                } else {
                    draw_char(connect_y, x, '-');
                }
            }
            
            // Desenhar linha vertical do filho
            for (int y = connect_y + 1; y < child_top; y++) {
                draw_char(y, child_center, '|');
            }
        }
    }
    
    attroff(COLOR_PAIR(5));
    attrset(A_NORMAL); // Limpar atributos
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

// NOVA FUNÇÃO: Layout mais inteligente para árvores pequenas
static void layout_tree_nodes(BPTreeNode *node, VisualNode *parent, int child_idx,
                             int level, TreeVisualizer *tv, int screen_width, int screen_height) {
    if (!node) return;
    
    // Calcular dimensões para todos os nós primeiro
    int total_levels = calculate_tree_depth(node, 0);
    
    // Calcular espaçamento vertical
    int vertical_spacing;
    if (total_levels <= 3) {
        vertical_spacing = 12; // Mais espaço para árvores pequenas
    } else {
        vertical_spacing = 8;
    }
    
    // Altura máxima baseada na profundidade
    int max_height_needed = total_levels * vertical_spacing;
    int start_y;
    
    if (max_height_needed < screen_height - 20) {
        // Árvore cabe confortavelmente
        start_y = 10;
    } else {
        // Árvore muito profunda, começar mais no topo
        start_y = 5;
    }
    
    // Calcular espaçamento horizontal baseado no nível
    int root_x = screen_width / 2;
    
    // Para árvores pequenas, usar espaçamento mais amplo
    int base_spacing;
    if (total_levels <= 2) {
        base_spacing = screen_width / 3;
    } else if (total_levels <= 4) {
        base_spacing = screen_width / 4;
    } else {
        base_spacing = screen_width / 6;
    }
    
    // Chamar collect_nodes com parâmetros ajustados
    collect_nodes(node, parent, child_idx, level, tv, root_x, start_y, 
                 base_spacing, screen_width);
}

// Função auxiliar adicional para detectar se a árvore cabe na tela
static bool tree_fits_screen(TreeVisualizer *tv, int screen_width, int screen_height) {
    int min_x = screen_width;
    int max_x = 0;
    int min_y = screen_height;
    int max_y = 0;
    
    for (int i = 0; i < tv->count; i++) {
        VisualNode *vn = tv->nodes[i];
        if (vn->coords.x < min_x) min_x = vn->coords.x;
        if (vn->coords.x + vn->coords.width > max_x) max_x = vn->coords.x + vn->coords.width;
        if (vn->coords.y < min_y) min_y = vn->coords.y;
        if (vn->coords.y + vn->coords.height > max_y) max_y = vn->coords.y + vn->coords.height;
    }
    
    int required_width = max_x - min_x + 20; // +20 para margens
    int required_height = max_y - min_y + 15; // +15 para margens e título
    
    return (required_width <= screen_width && required_height <= screen_height);
}

// Funções auxiliares para contar nós
static int contar_nos_arvore(BPTreeNode *node) {
    if (!node) return 0;
    
    int count = 1; // Contar este nó
    
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            if (node->children[i]) {
                count += contar_nos_arvore(node->children[i]);
            }
        }
    }
    
    return count;
}

static int contar_folhas(BPTreeNode *node) {
    if (!node) return 0;
    
    if (node->is_leaf) {
        return 1;
    }
    
    int count = 0;
    for (int i = 0; i <= node->num_keys; i++) {
        if (node->children[i]) {
            count += contar_folhas(node->children[i]);
        }
    }
    
    return count;
}

// Função principal para mostrar a árvore B+ real - VERSÃO CORRIGIDA
// Função principal para mostrar a árvore B+ real - VERSÃO CORRIGIDA
void mostrar_arvore_bplus_real(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio) {
    if (!tree || !tree->root) {
        // Mostrar mensagem se não houver árvore
        attrset(A_NORMAL);
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(10, 20, "! Nenhuma arvore B+ carregada!");
        mvprintw(11, 15, "Jogue algumas partidas para gerar estatisticas");
        attroff(COLOR_PAIR(3) | A_BOLD);
        return;
    }
    
    // Calcular dimensões da tela
    int screen_height = getmaxy(stdscr);
    int screen_width = getmaxx(stdscr);
    
    // Calcular profundidade da árvore
    int tree_depth = calculate_tree_depth(tree->root, 0);
    
    // Criar visualizador
    TreeVisualizer *tv = visualizer_create(screen_width, screen_height);
    
    // Usar layout melhorado
    layout_tree_nodes(tree->root, NULL, -1, 0, tv, screen_width, screen_height);
    
    // Limpar atributos antes de desenhar texto informativo
    attrset(A_NORMAL);
    
    // Desenhar título e informações - área mais compacta para árvores pequenas
    int title_y = 1;
    if (tree_depth <= 2) {
        title_y = 1;
    } else {
        title_y = 1;
    }
    
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(title_y, 2, "+==============================================================+");
    mvprintw(title_y + 1, 2, "|           VISUALIZACAO DA ARVORE B+ REAL           |");
    mvprintw(title_y + 2, 2, "+==============================================================+");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    // Informações sobre a árvore
    int info_y = title_y + 4;
    attron(COLOR_PAIR(3));
    mvprintw(info_y, 2, "Estatisticas da Arvore:");
    attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(2));
    mvprintw(info_y + 1, 4, "- Profundidade: %d niveis", tree_depth + 1);
    mvprintw(info_y + 2, 4, "- Total de nos: %d", tv->count);
    mvprintw(info_y + 3, 4, "- Ordem: %d", ORDER);
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(4));
    mvprintw(info_y + 4, 4, "- Criterio: %s", 
            criterio == RANKING_DANO ? "Maior Dano" :
            criterio == RANKING_VITORIAS ? "Mais Vitorias" : "Maior Distancia");
    attroff(COLOR_PAIR(4));
    
    // CORREÇÃO DA LEGENDA - CORRESPONDÊNCIA EXATA COM AS CORES DOS NÓS
    int legend_y = screen_height - 9;
    if (tv->max_depth <= 2) {
        legend_y = screen_height - 7;
    }
    
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(legend_y, 2, "LEGENDA DE CORES:");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // 1º lugar - AMARELO (color pair 3) - correspondente à cor usada nos nós
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(legend_y + 1, 4, "🥇 1º Lugar - Cor Dourada");
    attroff(COLOR_PAIR(3) | A_BOLD);
    
    // 2º lugar - CIANO (color pair 5) - correspondente à cor usada nos nós
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(legend_y + 2, 4, "🥈 2º Lugar - Cor Prateada");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // 3º lugar - VERMELHO (color pair 1) - correspondente à cor usada nos nós
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(legend_y + 3, 4, "🥉 3º Lugar - Cor Bronze");
    attroff(COLOR_PAIR(1) | A_BOLD);
    
    // Outras posições - VERDE (color pair 4) - correspondente à cor usada nos nós
    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(legend_y + 4, 4, "📊 Outras posicoes - Cor Verde");
    attroff(COLOR_PAIR(4) | A_BOLD);
    
    // Nós internos - AZUL (color pair 2) - correspondente à cor usada nos nós
    // NOTA: Nos nós internos usamos color pair 5 (ciano), mas na função
    // draw_tree_node, nós internos usam color_pair = 5 (ciano)
    // Para consistência, vamos manter como CIANO também na legenda
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(legend_y + 5, 4, "🌳 Nos internos - Cor Azul/Ciano");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // Instruções
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(screen_height - 1, 2, "ESC: Voltar | 1/2/3: Mudar criterio");
    attroff(COLOR_PAIR(2) | A_BOLD);
    
    // Desenhar conexões primeiro (para ficarem atrás dos nós)
    attrset(A_NORMAL);
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
                    break;
                }
            }
        }
        
        attrset(A_NORMAL);
        draw_tree_node(vn, criterio, ranking_position);
        attrset(A_NORMAL);
    }
    
    // Informação sobre navegação se a árvore for muito grande
    if (tv->count > 10 || tree_depth > 3) {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(screen_height - 3, screen_width - 40, "Aumente o terminal para melhor visualizacao");
        attroff(COLOR_PAIR(3) | A_BOLD);
    }
    
    // Liberar memória do visualizador
    visualizer_free(tv);
    
    // Garantir que os atributos sejam resetados
    attrset(A_NORMAL);
}

// Versão alternativa para mostrar árvore com scroll se necessário
void mostrar_arvore_com_scroll(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio) {
    if (!tree || !tree->root) {
        attrset(A_NORMAL);
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(10, 20, "! Nenhuma arvore B+ carregada!");
        mvprintw(11, 15, "Jogue algumas partidas para gerar estatisticas");
        attroff(COLOR_PAIR(3) | A_BOLD);
        return;
    }
    
    int screen_height = getmaxy(stdscr);
    int screen_width = getmaxx(stdscr);
    int tree_depth = calculate_tree_depth(tree->root, 0);
    
    // Tentar layout normal primeiro
    TreeVisualizer *tv = visualizer_create(screen_width, screen_height);
    layout_tree_nodes(tree->root, NULL, -1, 0, tv, screen_width, screen_height);
    
    // Verificar se cabe na tela
    if (!tree_fits_screen(tv, screen_width, screen_height)) {
        // Se não couber, mostrar mensagem
        visualizer_free(tv);
        
        clear();
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(5, 10, "Arvore muito grande para a tela atual!");
        mvprintw(6, 10, "Profundidade: %d niveis", tree_depth + 1);
        mvprintw(7, 10, "Largura do terminal: %d colunas", screen_width);
        mvprintw(8, 10, "Altura do terminal: %d linhas", screen_height);
        mvprintw(10, 10, "Sugestoes:");
        attroff(A_BOLD | COLOR_PAIR(3));
        
        attron(COLOR_PAIR(4));
        mvprintw(11, 12, "1. Aumente o tamanho do terminal");
        mvprintw(12, 12, "2. Reduza a janela para ver a arvore completa");
        mvprintw(13, 12, "3. Ou pressione qualquer tecla para visualizacao simplificada");
        attroff(COLOR_PAIR(4));
        
        attron(COLOR_PAIR(5) | A_BOLD);
        mvprintw(15, 10, "Pressione ESC para voltar ou ENTER para continuar...");
        attroff(COLOR_PAIR(5) | A_BOLD);
        
        refresh();
        
        int ch = getch();
        if (ch == 27) { // ESC
            return;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            // Mostrar visualização simplificada
            mostrar_arvore_simplificada(tree, ranking, ranking_count, criterio);
            return;
        }
    }
    
    // Se couber, mostrar normalmente
    clear();
    mostrar_arvore_bplus_real(tree, ranking, ranking_count, criterio);
    visualizer_free(tv);
}

// Visualização simplificada para árvores que não cabem na tela
// Visualização simplificada para árvores que não cabem na tela
void mostrar_arvore_simplificada(BPTree *tree, RankingEntry *ranking, int ranking_count, RankingCriterio criterio) {
    if (!tree || !tree->root) return;
    
    clear();
    
    attrset(A_NORMAL);
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(1, 2, "+========================================================+");
    mvprintw(2, 2, "|        VISUALIZACAO SIMPLIFICADA - ARVORE B+          |");
    mvprintw(3, 2, "+========================================================+");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    // Calcular estatísticas
    int tree_depth = calculate_tree_depth(tree->root, 0);
    int total_nodes = contar_nos_arvore(tree->root);
    int total_folhas = contar_folhas(tree->root);
    
    attron(COLOR_PAIR(3));
    mvprintw(5, 4, "ESTATISTICAS DA ARVORE:");
    attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(2));
    mvprintw(6, 6, "Profundidade total: %d niveis", tree_depth + 1);
    mvprintw(7, 6, "Total de nos: %d", total_nodes);
    mvprintw(8, 6, "Nos folha: %d", total_folhas);
    mvprintw(9, 6, "Ordem da arvore: %d", ORDER);
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(4));
    mvprintw(10, 6, "Criterio de ranking: %s", 
            criterio == RANKING_DANO ? "Maior Dano" :
            criterio == RANKING_VITORIAS ? "Mais Vitorias" : "Maior Distancia");
    attroff(COLOR_PAIR(4));
    
    // Mostrar os top 5 do ranking COM CORRESPONDÊNCIA DE CORES
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(12, 4, "TOP 5 - RANKING ATUAL (correspondente as cores da arvore):");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    if (ranking_count > 0) {
        int limit = (ranking_count < 5) ? ranking_count : 5;
        for (int i = 0; i < limit; i++) {
            int stat_value;
            switch (criterio) {
                case RANKING_DANO: stat_value = ranking[i].stats.cont_dano; break;
                case RANKING_VITORIAS: stat_value = ranking[i].stats.cont_vitorias; break;
                case RANKING_DISTANCIA: stat_value = ranking[i].stats.distancia_percorrida; break;
                default: stat_value = 0;
            }
            
            // Escolher cor baseado na posição - CORRESPONDÊNCIA EXATA COM AS CORES DA ÁRVORE
            int color;
            if (i == 0) {
                color = 3; // AMARELO/DOURADO para 1º lugar
            } else if (i == 1) {
                color = 5; // CIANO/PRATA para 2º lugar
            } else if (i == 2) {
                color = 1; // VERMELHO/BRONZE para 3º lugar
            } else {
                color = 4; // VERDE para outras posições
            }
            
            attron(COLOR_PAIR(color) | A_BOLD);
            char medal[10];
            if (i == 0) strcpy(medal, "🥇");
            else if (i == 1) strcpy(medal, "🥈");
            else if (i == 2) strcpy(medal, "🥉");
            else sprintf(medal, "%d.", i + 1);
            
            mvprintw(13 + i, 6, "%s %-15s: %d", medal, ranking[i].nome, stat_value);
            attroff(COLOR_PAIR(color) | A_BOLD);
        }
    }
    
    // Legenda de cores simplificada
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(19, 4, "LEGENDA DE CORES (correspondente aos nos da arvore):");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // 1º lugar
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(20, 6, "🥇 1º Lugar - Cor Dourada");
    attroff(COLOR_PAIR(3) | A_BOLD);
    
    // 2º lugar
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(21, 6, "🥈 2º Lugar - Cor Prateada");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // 3º lugar
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(22, 6, "🥉 3º Lugar - Cor Bronze");
    attroff(COLOR_PAIR(1) | A_BOLD);
    
    // Outras posições
    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(23, 6, "📊 Outras posicoes - Cor Verde");
    attroff(COLOR_PAIR(4) | A_BOLD);
    
    // Nós internos
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(24, 6, "🌳 Nos internos - Cor Azul/Ciano");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    // Informação sobre estrutura
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(26, 4, "ESTRUTURA DA ARVORE B+:");
    attroff(COLOR_PAIR(3) | A_BOLD);
    
    attron(COLOR_PAIR(2));
    mvprintw(27, 6, "- Todos os dados estao nas folhas");
    mvprintw(28, 6, "- Folhas estao todas no mesmo nivel");
    mvprintw(29, 6, "- Nos internos contem apenas chaves de roteamento");
    mvprintw(30, 6, "- Balanceamento automatico garantido");
    attroff(COLOR_PAIR(2));
    
    // Instruções
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(32, 4, "INSTRUCOES:");
    attroff(COLOR_PAIR(5) | A_BOLD);
    
    attron(COLOR_PAIR(4));
    mvprintw(33, 6, "Para ver a arvore completa, aumente o tamanho do terminal");
    mvprintw(34, 6, "ou reduza a quantidade de dados na arvore");
    attroff(COLOR_PAIR(4));
    
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(36, 10, "Pressione qualquer tecla para voltar...");
    attroff(COLOR_PAIR(1) | A_BOLD);
    
    refresh();
    getch();
}

// Nova função para mostrar menu de visualização da árvore - VERSÃO ATUALIZADA
void mostrar_menu_arvore_ranking(BPTree *tree) {
    if (!tree) return;
    
    // Carregar dados para ranking
    RankingEntry *ranking_array = NULL;
    int count = 0;
    bool dados_carregados = ler_dados_arquivo("data.txt", &ranking_array, &count);
    
    if (!dados_carregados || count == 0) {
        clear();
        attrset(A_NORMAL);
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(10, 20, "Nenhum dado de ranking disponivel!");
        mvprintw(11, 15, "Jogue algumas partidas para gerar estatisticas");
        mvprintw(13, 20, "Pressione qualquer tecla para voltar...");
        attroff(A_BOLD | COLOR_PAIR(3));
        refresh();
        getch();
        return;
    }
    
    RankingCriterio criterio_atual = RANKING_DANO;
    ordenar_ranking(ranking_array, count, criterio_atual);
    
    int sair = 0;
    
    while (!sair) {
        clear();
        
        // Verificar tamanho da tela antes de mostrar
        int screen_height = getmaxy(stdscr);
        int screen_width = getmaxx(stdscr);
        
        if (screen_width < 80 || screen_height < 24) {
            // Tela muito pequena
            attron(A_BOLD | COLOR_PAIR(3));
            mvprintw(5, 10, "Tela muito pequena para visualizar a arvore!");
            mvprintw(6, 10, "Largura atual: %d (minimo 80)", screen_width);
            mvprintw(7, 10, "Altura atual: %d (minimo 24)", screen_height);
            mvprintw(9, 10, "Aumente o tamanho do terminal e tente novamente");
            attroff(A_BOLD | COLOR_PAIR(3));
            
            attron(COLOR_PAIR(5));
            mvprintw(12, 10, "Pressione ESC para voltar ou R para recarregar...");
            attroff(COLOR_PAIR(5));
            
            refresh();
            
            int ch = getch();
            if (ch == 27) {
                sair = 1;
            }
            // 'r' ou 'R' faz recarregar
            continue;
        }
        
        // Mostrar a árvore B+ real com verificação de tamanho
        mostrar_arvore_com_scroll(tree, ranking_array, count, criterio_atual);
        
        // Menu de controle na parte superior
        attrset(A_NORMAL);
        attron(A_BOLD | COLOR_PAIR(5));
        mvprintw(0, 2, "+------------------------------------------------------+");
        mvprintw(1, 2, "|               CONTROLES DA ARVORE B+                |");
        mvprintw(2, 2, "+------------------------------------------------------+");
        attroff(A_BOLD | COLOR_PAIR(5));
        
        // Opções de critério
        attrset(A_NORMAL);
        if (criterio_atual == RANKING_DANO) {
            attron(COLOR_PAIR(1) | A_REVERSE);
        } else {
            attron(COLOR_PAIR(1));
        }
        mvprintw(3, 4, " [1] Por Dano ");
        attroff(COLOR_PAIR(1) | A_REVERSE);
        
        attrset(A_NORMAL);
        if (criterio_atual == RANKING_VITORIAS) {
            attron(COLOR_PAIR(4) | A_REVERSE);
        } else {
            attron(COLOR_PAIR(4));
        }
        mvprintw(3, 20, " [2] Por Vitorias ");
        attroff(COLOR_PAIR(4) | A_REVERSE);
        
        attrset(A_NORMAL);
        if (criterio_atual == RANKING_DISTANCIA) {
            attron(COLOR_PAIR(2) | A_REVERSE);
        } else {
            attron(COLOR_PAIR(2));
        }
        mvprintw(3, 40, " [3] Por Distancia ");
        attroff(COLOR_PAIR(2) | A_REVERSE);
        
        attrset(A_NORMAL);
        attron(COLOR_PAIR(3));
        mvprintw(3, 60, " [ESC] Voltar ");
        attroff(COLOR_PAIR(3));
        
        attron(COLOR_PAIR(5));
        mvprintw(4, 2, "+------------------------------------------------------+");
        attroff(COLOR_PAIR(5));
        
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
                
            case 27: // ESC
                sair = 1;
                break;
                
            case 'r':
            case 'R':
                // Recarregar (nada a fazer, loop continua)
                break;
        }
    }
    
    // Liberar memória
    liberar_array_ranking(ranking_array);
    
    // Resetar atributos ao sair
    attrset(A_NORMAL);
}