#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void loginUser(const char *firstName, const char *surname, int *loggedIn) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Error opening user data file.\n");
        return;
    }

    char line[256];
    *loggedIn = 0;  // Reset the logged-in status to 0
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;  // Remove newline character
        char *fileFirstName = strtok(line, ",");   // Parse the first name
        char *fileSurname = strtok(NULL, ",");     // Parse the surname

        if (fileFirstName && fileSurname && strcmp(firstName, fileFirstName) == 0 && strcmp(surname, fileSurname) == 0) {
            *loggedIn = 1;  // Set the flag via pointer if both match
            break;
        }
    }
    fclose(file);

    if (*loggedIn) {
        printf("Login successful!\n");
    } else {
        printf("Login failed: Incorrect first name or surname.\n");
    }
}

void createAccount(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "a+");
    if (!file) {
        printf("Error opening user data file.\n");
        return;
    }

    rewind(file);  // Ensure we start reading from the start
    char line[256];
    int exists = 0;
    while (fgets(line, sizeof(line), file)) {
        char *fileUsername = strtok(line, ",");
        if (fileUsername && strcmp(username, fileUsername) == 0) {
            printf("Account creation failed: Username already exists.\n");
            exists = 1;
            break;
        }
    }

    if (!exists) {
        fprintf(file, "%s,%s\n", username, password);  // Append new user
        printf("Account created successfully!\n");
    }
    fclose(file);
}