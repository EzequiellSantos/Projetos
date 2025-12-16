#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>

/* Simple user record for this project */
#define AUTH_USERNAME_MAX 32
#define AUTH_PASSWORD_MAX 64

typedef struct UserRecord {
    int id;
    char username[AUTH_USERNAME_MAX];
    char password[AUTH_PASSWORD_MAX];
} UserRecord;

/* Register a new user. Returns new user id on success, -1 on failure (username exists or IO error). */
int auth_register(const char *username, const char *password);

/* Login: returns user id on success, -1 on failure. */
int auth_login(const char *username, const char *password);

/* Find user by username; returns true if found and fills out (optional). */
bool auth_find_user(const char *username, UserRecord *out);

#endif
