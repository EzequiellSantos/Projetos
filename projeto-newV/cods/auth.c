#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/auth.h"

static const char *USERS_DB = "users.db";

/* 
* Procura um usuário pelo `username` no arquivo de usuários.
* Se encontrado, copia o registro para `out` (se não for NULL) e retorna true.
* Retorna false se o usuário não existir ou se ocorrer erro ao abrir o arquivo.
*/
bool auth_find_user(const char *username, UserRecord *out) {
    FILE *f = fopen(USERS_DB, "rb");
    if (!f) return false;
    UserRecord ur;
    while (fread(&ur, sizeof(UserRecord), 1, f) == 1) {
        if (strncmp(ur.username, username, AUTH_USERNAME_MAX) == 0) {
            if (out) *out = ur;
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}

/*
* Calcula o próximo ID disponível lendo todos os registros e retornando o maior + 1.
*/
static int next_id(void) {
    FILE *f = fopen(USERS_DB, "rb");
    int maxid = 0;
    if (!f) return 1; // start at 1 if file doesn't exist
    UserRecord ur;
    while (fread(&ur, sizeof(UserRecord), 1, f) == 1) {
        if (ur.id > maxid) maxid = ur.id;
    }
    fclose(f);
    return maxid + 1;
}

/*
* Registra um novo usuário com `username` e `password`
* Realiza as verificações para que o login ocorra com sucesso
*/

int auth_register(const char *username, const char *password) {
    if (!username || !password) return -1;
    if (strlen(username) == 0 || strlen(password) == 0) return -1;
    if (strlen(username) >= AUTH_USERNAME_MAX) return -1;
    if (strlen(password) >= AUTH_PASSWORD_MAX) return -1;

    UserRecord existing;
    if (auth_find_user(username, &existing)) {
        return -1; // user exists
    }

    UserRecord ur;
    ur.id = next_id();
    memset(ur.username, 0, AUTH_USERNAME_MAX);
    memset(ur.password, 0, AUTH_PASSWORD_MAX);
    strncpy(ur.username, username, AUTH_USERNAME_MAX-1);
    strncpy(ur.password, password, AUTH_PASSWORD_MAX-1);

    FILE *f = fopen(USERS_DB, "ab");
    if (!f) return -1;
    size_t w = fwrite(&ur, sizeof(UserRecord), 1, f);
    fclose(f);
    if (w != 1) return -1;
    return ur.id;
}

/* 
*Verifica credenciais de login; retorna o `id` do usuário em caso de sucesso.
* Retorna -1 em caso de falha (usuário não encontrado ou senha inválida).
*/
int auth_login(const char *username, const char *password) {
    UserRecord ur;
    if (!auth_find_user(username, &ur)) return -1;
    if (strncmp(ur.password, password, AUTH_PASSWORD_MAX) == 0) return ur.id;
    return -1;
}
