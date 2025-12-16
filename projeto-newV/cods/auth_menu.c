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
    
    while (1) {
        clear();
        
        // Título
        mvprintw(2, 2, "=== BOMBERMAN - LOGIN ===");
        mvprintw(4, 4, "1. Login");
        mvprintw(5, 4, "2. Registrar");
        mvprintw(6, 4, "3. Sair");
        mvprintw(8, 4, "Escolha uma opcao: ");
        
        // Destacar opção selecionada
        mvprintw(4 + opcao, 3, ">");
        
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
        }
    }
}

int realizar_login(void) {
    echo();
    
    char username[AUTH_USERNAME_MAX];
    char password[AUTH_PASSWORD_MAX];
    
    clear();
    mvprintw(2, 2, "=== LOGIN ===");
    
    mvprintw(4, 4, "Usuario: ");
    getnstr(username, AUTH_USERNAME_MAX - 1);
    
    mvprintw(5, 4, "Senha: ");
    getnstr(password, AUTH_PASSWORD_MAX - 1);
    
    noecho();
    
    int user_id = auth_login(username, password);
    
    if (user_id >= 0) {
        clear();
        mvprintw(2, 2, "Login realizado com sucesso!");
        mvprintw(4, 4, "Bem-vindo, %s!", username);
        mvprintw(6, 4, "ID do usuario: %d", user_id);
        mvprintw(8, 4, "Pressione qualquer tecla para continuar...");
        getch();
        return user_id;
    } else {
        clear();
        mvprintw(2, 2, "ERRO: Login falhou!");
        mvprintw(4, 4, "Usuario ou senha incorretos.");
        mvprintw(6, 4, "Pressione qualquer tecla para tentar novamente...");
        getch();
        return -1;
    }
}

int realizar_registro(void) {
    echo();
    
    char username[AUTH_USERNAME_MAX];
    char password[AUTH_PASSWORD_MAX];
    
    clear();
    mvprintw(2, 2, "=== REGISTRO ===");
    
    mvprintw(4, 4, "Novo usuario: ");
    getnstr(username, AUTH_USERNAME_MAX - 1);
    
    mvprintw(5, 4, "Nova senha: ");
    getnstr(password, AUTH_PASSWORD_MAX - 1);
    
    noecho();
    
    int user_id = auth_register(username, password);
    
    if (user_id >= 0) {
        clear();
        mvprintw(2, 2, "Registro realizado com sucesso!");
        mvprintw(4, 4, "Usuario: %s", username);
        mvprintw(5, 4, "ID: %d", user_id);
        mvprintw(7, 4, "Pressione qualquer tecla para continuar...");
        getch();
        return user_id;
    } else {
        clear();
        mvprintw(2, 2, "ERRO: Registro falhou!");
        mvprintw(4, 4, "Usuario ja existe ou dados invalidos.");
        mvprintw(6, 4, "Pressione qualquer tecla para tentar novamente...");
        getch();
        return -1;
    }
}

void mostrar_tela_boas_vindas(int user_id) {
    clear();
    
    // Arte ASCII do Bomberman
    mvprintw(2, 2, "  ____                         __  __            ");
    mvprintw(3, 2, " |  _ \\                       |  \\/  |           ");
    mvprintw(4, 2, " | |_) | ___  _ __ ___   ___  | \\  / | __ _ _ __ ");
    mvprintw(5, 2, " |  _ < / _ \\| '_ ` _ \\ / _ \\ | |\\/| |/ _` | '__|");
    mvprintw(6, 2, " | |_) | (_) | | | | | |  __/ | |  | | (_| | |   ");
    mvprintw(7, 2, " |____/ \\___/|_| |_| |_|\\___| |_|  |_|\\__,_|_|   ");
    
    mvprintw(10, 2, "================================================");
    mvprintw(12, 2, "Bem-vindo ao Bomberman!");
    mvprintw(13, 2, "Usuario ID: %d", user_id);
    mvprintw(15, 2, "Controles:");
    mvprintw(16, 2, "  Jogador 1: W A S D");
    mvprintw(17, 2, "  Jogador 2: SETAS");
    mvprintw(18, 2, "  Sair: Q");
    mvprintw(20, 2, "Pressione qualquer tecla para selecionar personagens...");
    
    getch();
}