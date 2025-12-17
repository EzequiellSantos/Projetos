#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/auth.h"
#include "../includes/auth_menu.h"

int mostrar_menu_login(void) {
    int opcao = 0;
    int ch;
    
    // Desabilitar nodelay temporariamente para o menu
    nodelay(stdscr, FALSE);
    
    // Inicializar cores
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    
    while (1) {
        clear();
        
        // Título com design consistente
        attron(A_BOLD | COLOR_PAIR(5));
        mvprintw(2, 2, "╔═══════════════════════════════════════════════════╗");
        mvprintw(3, 2, "║               🔐 BOMBERMAN - LOGIN 🔐               ║");
        mvprintw(4, 2, "╚═══════════════════════════════════════════════════╝");
        attroff(A_BOLD | COLOR_PAIR(5));
        
        // Opções com emojis
        attron(COLOR_PAIR(2));
        mvprintw(7, 4, "1. 🔑 Login");
        mvprintw(8, 4, "2. 📝 Registrar");
        mvprintw(9, 4, "3. 🚪 Sair");
        
        // Instrução
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(12, 4, "Escolha uma opção: ");
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        // Destacar opção selecionada com design consistente
        if (opcao == 0) {
            attron(A_BOLD | A_REVERSE | COLOR_PAIR(4));
            mvprintw(7, 2, "▶");
            attroff(A_BOLD | A_REVERSE | COLOR_PAIR(4));
            attron(A_BOLD | COLOR_PAIR(5));
            mvprintw(7, 4, "1. 🔑 Login");
            attroff(A_BOLD | COLOR_PAIR(5));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(7, 2, " ");
            attroff(COLOR_PAIR(1));
        }
        
        if (opcao == 1) {
            attron(A_BOLD | A_REVERSE | COLOR_PAIR(4));
            mvprintw(8, 2, "▶");
            attroff(A_BOLD | A_REVERSE | COLOR_PAIR(4));
            attron(A_BOLD | COLOR_PAIR(3));
            mvprintw(8, 4, "2. 📝 Registrar");
            attroff(A_BOLD | COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(8, 2, " ");
            attroff(COLOR_PAIR(1));
        }
        
        if (opcao == 2) {
            attron(A_BOLD | A_REVERSE | COLOR_PAIR(4));
            mvprintw(9, 2, "▶");
            attroff(A_BOLD | A_REVERSE | COLOR_PAIR(4));
            attron(A_BOLD | COLOR_PAIR(1));
            mvprintw(9, 4, "3. 🚪 Sair");
            attroff(A_BOLD | COLOR_PAIR(1));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(9, 2, " ");
            attroff(COLOR_PAIR(1));
        }
        
        ch = getch();
        
        switch (ch) {
            case KEY_UP:
                opcao = (opcao - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                opcao = (opcao + 1) % 3;
                break;
            case '\n':
            case KEY_ENTER:
                return opcao + 1;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case 'q': return 3;
            case 27: // ESC também sai
                return 3;
        }
    }
}

int realizar_login(void) {
    echo();
    
    char username[AUTH_USERNAME_MAX];
    char password[AUTH_PASSWORD_MAX];
    
    clear();
    
    // Título com design
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(2, 2, "╔═══════════════════════════════════════════════════╗");
    mvprintw(3, 2, "║                   🔑 LOGIN 🔑                     ║");
    mvprintw(4, 2, "╚═══════════════════════════════════════════════════╝");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    attron(COLOR_PAIR(3));
    mvprintw(6, 4, "Usuario: ");
    getnstr(username, AUTH_USERNAME_MAX - 1);
    
    mvprintw(7, 4, "Senha: ");
    getnstr(password, AUTH_PASSWORD_MAX - 1);
    attroff(COLOR_PAIR(3));
    
    noecho();
    
    int user_id = auth_login(username, password);
    
    if (user_id >= 0) {
        clear();
        attron(A_BOLD | COLOR_PAIR(4));
        mvprintw(4, 10, "✅ Login realizado com sucesso!");
        attroff(A_BOLD | COLOR_PAIR(4));
        
        attron(COLOR_PAIR(5));
        mvprintw(6, 10, "👤 Bem-vindo, %s!", username);
        attroff(COLOR_PAIR(5));
        
        attron(COLOR_PAIR(2));
        mvprintw(7, 10, "🔢 ID do usuario: %d", user_id);
        attroff(COLOR_PAIR(2));
        
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(10, 10, "Pressione qualquer tecla para continuar...");
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        getch();
        return user_id;
    } else {
        clear();
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(4, 10, "❌ ERRO: Login falhou!");
        attroff(A_BOLD | COLOR_PAIR(1));
        
        attron(COLOR_PAIR(3));
        mvprintw(6, 10, "Usuario ou senha incorretos.");
        attroff(COLOR_PAIR(3));
        
        attron(COLOR_PAIR(5) | A_BOLD);
        mvprintw(8, 10, "Pressione qualquer tecla para tentar novamente...");
        attroff(COLOR_PAIR(5) | A_BOLD);
        
        getch();
        return -1;
    }
}

int realizar_registro(void) {
    echo();
    
    char username[AUTH_USERNAME_MAX];
    char password[AUTH_PASSWORD_MAX];
    
    clear();
    
    // Título com design
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(2, 2, "╔═══════════════════════════════════════════════════╗");
    mvprintw(3, 2, "║                 📝 REGISTRO 📝                    ║");
    mvprintw(4, 2, "╚═══════════════════════════════════════════════════╝");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    attron(COLOR_PAIR(3));
    mvprintw(6, 4, "📝 Novo usuario: ");
    getnstr(username, AUTH_USERNAME_MAX - 1);
    
    mvprintw(7, 4, "🔒 Nova senha: ");
    getnstr(password, AUTH_PASSWORD_MAX - 1);
    attroff(COLOR_PAIR(3));
    
    noecho();
    
    int user_id = auth_register(username, password);
    
    if (user_id >= 0) {
        clear();
        attron(A_BOLD | COLOR_PAIR(4));
        mvprintw(4, 10, "✅ Registro realizado com sucesso!");
        attroff(A_BOLD | COLOR_PAIR(4));
        
        attron(COLOR_PAIR(5));
        mvprintw(6, 10, "👤 Usuario: %s", username);
        mvprintw(7, 10, "🔢 ID: %d", user_id);
        attroff(COLOR_PAIR(5));
        
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(10, 10, "Pressione qualquer tecla para continuar...");
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        getch();
        return user_id;
    } else {
        clear();
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(4, 10, "❌ ERRO: Registro falhou!");
        attroff(A_BOLD | COLOR_PAIR(1));
        
        attron(COLOR_PAIR(3));
        mvprintw(6, 10, "Usuario ja existe ou dados invalidos.");
        attroff(COLOR_PAIR(3));
        
        attron(COLOR_PAIR(5) | A_BOLD);
        mvprintw(8, 10, "Pressione qualquer tecla para tentar novamente...");
        attroff(COLOR_PAIR(5) | A_BOLD);
        
        getch();
        return -1;
    }
}

void mostrar_tela_boas_vindas(int user_id) {
    clear();
    
    // Inicializar cores
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    
    // Título com design
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(2, 2, "╔═══════════════════════════════════════════════════╗");
    mvprintw(3, 2, "║            🎮 BEM-VINDO AO BOMBERMAN 🎮            ║");
    mvprintw(4, 2, "╚═══════════════════════════════════════════════════╝");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    // Arte ASCII do Bomberman com cores
    attron(COLOR_PAIR(3));
    mvprintw(6, 20, "  ____                         __  __            ");
    mvprintw(7, 20, " |  _ \\                       |  \\/  |           ");
    mvprintw(8, 20, " | |_) | ___  _ __ ___   ___  | \\  / | __ _ _ __ ");
    mvprintw(9, 20, " |  _ < / _ \\| '_ ` _ \\ / _ \\ | |\\/| |/ _` | '__|");
    mvprintw(10, 20, " | |_) | (_) | | | | | |  __/ | |  | | (_| | |   ");
    mvprintw(11, 20, " |____/ \\___/|_| |_| |_|\\___| |_|  |_|\\__,_|_|   ");
    attroff(COLOR_PAIR(3));
    
    // Separador
    attron(COLOR_PAIR(2));
    mvprintw(13, 2, "═════════════════════════════════════════════════════");
    attroff(COLOR_PAIR(2));
    
    // Informações
    attron(COLOR_PAIR(4));
    mvprintw(15, 4, "👤 Usuario ID: %d", user_id);
    attroff(COLOR_PAIR(4));
    
    // Controles
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(17, 4, "🎮 Controles:");
    attroff(A_BOLD | COLOR_PAIR(5));
    
    attron(COLOR_PAIR(1));
    mvprintw(18, 6, "Jogador 1: W A S D + ESPAÇO (bomba)");
    attroff(COLOR_PAIR(1));
    
    attron(COLOR_PAIR(2));
    mvprintw(19, 6, "Jogador 2: SETAS + / (bomba)");
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(3));
    mvprintw(20, 6, "Sair: Q ou ESC");
    attroff(COLOR_PAIR(3));
    
    // Mensagem final
    attron(A_BOLD | COLOR_PAIR(4));
    mvprintw(23, 10, "🎯 Pressione qualquer tecla para selecionar personagens...");
    attroff(A_BOLD | COLOR_PAIR(4));
    
    getch();
}