#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../includes/ranking.h"

#define MAX_RANKING_ENTRIES 100
#define RANKING_WIDTH 80
#define RANKING_HEIGHT 24

// Estrutura para armazenar uma linha do arquivo
typedef struct {
    char nome[50];
    int vida;
    int vitorias;
    int distancia;
    int dano;
} ArquivoEntry;

// Função para extrair nome e stats de uma linha do arquivo
static bool parse_linha_arquivo(const char *linha, ArquivoEntry *entry) {
    // Formato esperado: "nome: vida=X, vitorias=Y, distancia=Z, dano=W"
    char nome[50];
    int vida, vitorias, distancia, dano;
    
    if (sscanf(linha, "%49[^:]: vida=%d, vitorias=%d, distancia=%d, dano=%d", 
               nome, &vida, &vitorias, &distancia, &dano) == 5) {
        strncpy(entry->nome, nome, 49);
        entry->nome[49] = '\0';
        entry->vida = vida;
        entry->vitorias = vitorias;
        entry->distancia = distancia;
        entry->dano = dano;
        return true;
    }
    return false;
}

// Função para ler dados do arquivo "data.txt"
bool ler_dados_arquivo(const char *filename, RankingEntry **array, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        *array = NULL;
        *count = 0;
        return false;
    }
    
    ArquivoEntry *temp = malloc(MAX_RANKING_ENTRIES * sizeof(ArquivoEntry));
    if (!temp) {
        fclose(file);
        return false;
    }
    
    char linha[256];
    int idx = 0;
    
    while (fgets(linha, sizeof(linha), file) && idx < MAX_RANKING_ENTRIES) {
        // Remover newline
        linha[strcspn(linha, "\n")] = 0;
        
        if (parse_linha_arquivo(linha, &temp[idx])) {
            idx++;
        }
    }
    
    fclose(file);
    
    // Converter para RankingEntry
    *array = malloc(idx * sizeof(RankingEntry));
    if (!*array) {
        free(temp);
        *count = 0;
        return false;
    }
    
    for (int i = 0; i < idx; i++) {
        strncpy((*array)[i].nome, temp[i].nome, 49);
        (*array)[i].nome[49] = '\0';
        (*array)[i].stats.vida = temp[i].vida;
        (*array)[i].stats.cont_vitorias = temp[i].vitorias;
        (*array)[i].stats.distancia_percorrida = temp[i].distancia;
        (*array)[i].stats.cont_dano = temp[i].dano;
        (*array)[i].posicao = 0;
    }
    
    free(temp);
    *count = idx;
    return true;
}

// Função de comparação para qsort - Dano
static int comparar_dano(const void *a, const void *b) {
    const RankingEntry *entry_a = (const RankingEntry *)a;
    const RankingEntry *entry_b = (const RankingEntry *)b;
    return entry_b->stats.cont_dano - entry_a->stats.cont_dano;
}

// Função de comparação para qsort - Vitórias
static int comparar_vitorias(const void *a, const void *b) {
    const RankingEntry *entry_a = (const RankingEntry *)a;
    const RankingEntry *entry_b = (const RankingEntry *)b;
    return entry_b->stats.cont_vitorias - entry_a->stats.cont_vitorias;
}

// Função de comparação para qsort - Distância
static int comparar_distancia(const void *a, const void *b) {
    const RankingEntry *entry_a = (const RankingEntry *)a;
    const RankingEntry *entry_b = (const RankingEntry *)b;
    return entry_b->stats.distancia_percorrida - entry_a->stats.distancia_percorrida;
}

// Ordenar array por critério
void ordenar_ranking(RankingEntry *array, int n, RankingCriterio criterio) {
    switch (criterio) {
        case RANKING_DANO:
            qsort(array, n, sizeof(RankingEntry), comparar_dano);
            break;
        case RANKING_VITORIAS:
            qsort(array, n, sizeof(RankingEntry), comparar_vitorias);
            break;
        case RANKING_DISTANCIA:
            qsort(array, n, sizeof(RankingEntry), comparar_distancia);
            break;
    }
    
    // Atualizar posições
    for (int i = 0; i < n; i++) {
        array[i].posicao = i + 1;
    }
}

// Liberar array
void liberar_array_ranking(RankingEntry *array) {
    if (array) {
        free(array);
    }
}

// Desenhar cabeçalho do ranking
static void desenhar_cabecalho(int start_x, int start_y, RankingCriterio criterio) {
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(start_y, start_x, "┌────────────────────────────────────────────────────────────┐");
    mvprintw(start_y + 1, start_x, "│                    🏆 RANKING BOMBERMAN 🏆                 │");
    mvprintw(start_y + 2, start_x, "└────────────────────────────────────────────────────────────┘");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    // Categorias
    int cat_x = start_x + 5;
    int cat_y = start_y + 4;
    
    attron(COLOR_PAIR(3));
    mvprintw(cat_y, cat_x, "Categorias:");
    attroff(COLOR_PAIR(3));
    
    // Destacar categoria selecionada
    if (criterio == RANKING_DANO) {
        attron(A_BOLD | COLOR_PAIR(1) | A_REVERSE);
    } else {
        attron(COLOR_PAIR(1));
    }
    mvprintw(cat_y + 1, cat_x, " 1. Maior Dano ");
    if (criterio == RANKING_DANO) {
        attroff(A_BOLD | COLOR_PAIR(1) | A_REVERSE);
    } else {
        attroff(COLOR_PAIR(1));
    }
    
    if (criterio == RANKING_VITORIAS) {
        attron(A_BOLD | COLOR_PAIR(4) | A_REVERSE);
    } else {
        attron(COLOR_PAIR(4));
    }
    mvprintw(cat_y + 2, cat_x, " 2. Mais Vitórias ");
    if (criterio == RANKING_VITORIAS) {
        attroff(A_BOLD | COLOR_PAIR(4) | A_REVERSE);
    } else {
        attroff(COLOR_PAIR(4));
    }
    
    if (criterio == RANKING_DISTANCIA) {
        attron(A_BOLD | COLOR_PAIR(2) | A_REVERSE);
    } else {
        attron(COLOR_PAIR(2));
    }
    mvprintw(cat_y + 3, cat_x, " 3. Maior Distância ");
    if (criterio == RANKING_DISTANCIA) {
        attroff(A_BOLD | COLOR_PAIR(2) | A_REVERSE);
    } else {
        attroff(COLOR_PAIR(2));
    }
    
    // Instruções
    attron(COLOR_PAIR(5));
    mvprintw(cat_y + 5, cat_x, "Controles:");
    mvprintw(cat_y + 6, cat_x, "• 1-3: Mudar categoria");
    mvprintw(cat_y + 7, cat_x, "• ESC: Voltar ao menu");
    attroff(COLOR_PAIR(5));
}

// Desenhar tabela de ranking
static void desenhar_tabela(RankingEntry *array, int count, int start_x, int start_y, RankingCriterio criterio) {
    int table_y = start_y + 11;
    int table_x = start_x + 2;
    
    // Cabeçalho da tabela
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(table_y - 1, table_x, "┌───┬────────────────────┬──────────────┬─────────────┬──────────┐");
    mvprintw(table_y, table_x,     "│ # │       NOME        │    DANO      │  VITÓRIAS   │ DISTÂNCIA│");
    mvprintw(table_y + 1, table_x, "├───┼────────────────────┼──────────────┼─────────────┼──────────┤");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    // Linhas da tabela
    int max_linhas = 10; // Mostrar apenas top 10
    if (count > max_linhas) count = max_linhas;
    
    for (int i = 0; i < count; i++) {
        int linha = table_y + 2 + i;
        
        // Cor da posição (medalhas para top 3)
        if (i == 0) {
            attron(COLOR_PAIR(3) | A_BOLD); // Ouro
        } else if (i == 1) {
            attron(COLOR_PAIR(5) | A_BOLD); // Prata
        } else if (i == 2) {
            attron(COLOR_PAIR(1) | A_BOLD); // Bronze
        } else {
            attron(COLOR_PAIR(2));
        }
        
        // Posição com emoji para top 3
        if (i == 0) {
            mvprintw(linha, table_x, "│🥇 ");
        } else if (i == 1) {
            mvprintw(linha, table_x, "│🥈 ");
        } else if (i == 2) {
            mvprintw(linha, table_x, "│🥉 ");
        } else {
            mvprintw(linha, table_x, "│%2d ", i + 1);
        }
        
        // Nome (destacar se for top 3)
        if (i < 3) {
            attron(A_BOLD);
        }
        mvprintw(linha, table_x + 4, "│ %-18s ", array[i].nome);
        if (i < 3) {
            attroff(A_BOLD);
        }
        
        // Dano (destacar se categoria for dano)
        if (criterio == RANKING_DANO) {
            attron(A_BOLD | COLOR_PAIR(1));
        }
        mvprintw(linha, table_x + 24, "│ %-12d ", array[i].stats.cont_dano);
        if (criterio == RANKING_DANO) {
            attroff(A_BOLD | COLOR_PAIR(1));
        }
        
        // Vitórias (destacar se categoria for vitórias)
        if (criterio == RANKING_VITORIAS) {
            attron(A_BOLD | COLOR_PAIR(4));
        }
        mvprintw(linha, table_x + 39, "│ %-11d ", array[i].stats.cont_vitorias);
        if (criterio == RANKING_VITORIAS) {
            attroff(A_BOLD | COLOR_PAIR(4));
        }
        
        // Distância (destacar se categoria for distância)
        if (criterio == RANKING_DISTANCIA) {
            attron(A_BOLD | COLOR_PAIR(2));
        }
        mvprintw(linha, table_x + 53, "│ %-8d ", array[i].stats.distancia_percorrida);
        if (criterio == RANKING_DISTANCIA) {
            attroff(A_BOLD | COLOR_PAIR(2));
        }
        
        mvprintw(linha, table_x + 64, "│");
        
        // Resetar cores
        if (i < 3) {
            attroff(COLOR_PAIR(3) | COLOR_PAIR(5) | COLOR_PAIR(1) | A_BOLD);
        } else {
            attroff(COLOR_PAIR(2));
        }
    }
    
    // Rodapé da tabela
    attron(COLOR_PAIR(5));
    mvprintw(table_y + 2 + count, table_x, "└───┴────────────────────┴──────────────┴─────────────┴──────────┘");
    attroff(COLOR_PAIR(5));
    
    // Mensagem se não houver dados
    if (count == 0) {
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(table_y + 5, table_x + 15, "📭 Nenhum dado de ranking disponível!");
        mvprintw(table_y + 6, table_x + 10, "Jogue algumas partidas para gerar estatísticas");
        attroff(A_BOLD | COLOR_PAIR(3));
    }
}

// Tela principal do ranking
void mostrar_tela_ranking(void) {
    // Carregar dados do arquivo
    RankingEntry *ranking_array = NULL;
    int count = 0;
    bool dados_carregados = ler_dados_arquivo("data.txt", &ranking_array, &count);
    
    RankingCriterio criterio_atual = RANKING_DANO;
    
    // Ordenar por dano inicialmente
    if (dados_carregados && count > 0) {
        ordenar_ranking(ranking_array, count, criterio_atual);
    }
    
    // Loop principal da tela
    int sair = 0;
    while (!sair) {
        clear();
        
        // Calcular posição central
        int screen_width, screen_height;
        getmaxyx(stdscr, screen_height, screen_width);
        
        int start_x = (screen_width - RANKING_WIDTH) / 2;
        int start_y = (screen_height - RANKING_HEIGHT) / 2;
        
        // Desenhar fundo
        attron(COLOR_PAIR(5));
        for (int x = start_x; x < start_x + RANKING_WIDTH; x++) {
            mvaddch(start_y, x, '-');
            mvaddch(start_y + RANKING_HEIGHT - 1, x, '-');
        }
        for (int y = start_y; y < start_y + RANKING_HEIGHT; y++) {
            mvaddch(y, start_x, '|');
            mvaddch(y, start_x + RANKING_WIDTH - 1, '|');
        }
        attroff(COLOR_PAIR(5));
        
        // Desenhar conteúdo
        desenhar_cabecalho(start_x + 5, start_y + 1, criterio_atual);
        
        if (dados_carregados && count > 0) {
            desenhar_tabela(ranking_array, count, start_x, start_y, criterio_atual);
        } else {
            attron(A_BOLD | COLOR_PAIR(3));
            mvprintw(start_y + RANKING_HEIGHT/2, start_x + RANKING_WIDTH/2 - 20, 
                    "Nenhum dado disponível. Jogue para gerar estatísticas!");
            attroff(A_BOLD | COLOR_PAIR(3));
        }
        
        // Rodapé
        attron(COLOR_PAIR(5));
        mvprintw(start_y + RANKING_HEIGHT - 3, start_x + 10, 
                "Dados carregados: %d jogadores", count);
        mvprintw(start_y + RANKING_HEIGHT - 2, start_x + 15, 
                "Pressione ESC para voltar");
        attroff(COLOR_PAIR(5));
        
        refresh();
        
        // Processar input
        int ch = getch();
        switch (ch) {
            case '1':
                criterio_atual = RANKING_DANO;
                if (dados_carregados && count > 0) {
                    ordenar_ranking(ranking_array, count, criterio_atual);
                }
                break;
                
            case '2':
                criterio_atual = RANKING_VITORIAS;
                if (dados_carregados && count > 0) {
                    ordenar_ranking(ranking_array, count, criterio_atual);
                }
                break;
                
            case '3':
                criterio_atual = RANKING_DISTANCIA;
                if (dados_carregados && count > 0) {
                    ordenar_ranking(ranking_array, count, criterio_atual);
                }
                break;
                
            case 27: // ESC
                sair = 1;
                break;
        }
    }
    
    // Liberar memória
    if (ranking_array) {
        liberar_array_ranking(ranking_array);
    }
}