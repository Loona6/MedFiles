
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ID_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_LINE_LENGTH 50 // Adjust according to maximum expected line length in the file

void admin_pass(char *mode);
int check_credentials(char *mode, char *user_id, char *password);

void admin_pass(char *mode) {
    char user_id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your user ID: ");
    fgets(user_id, MAX_ID_LENGTH, stdin);
    user_id[strcspn(user_id, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (check_credentials(mode, user_id, password)) {
        printf("Login successful!\n");
        // Add the function or actions to be taken after successful login
    } else {
        printf("Invalid user ID or password.\n");
    }
}

int check_credentials(char *mode, char *user_id, char *password) {
    FILE *file;
    char filename[30];
    char line[MAX_LINE_LENGTH]; // Buffer to read each line from the file
    char *file_mode = strdup(mode);

    // Convert mode to lowercase
    for (int i = 0; file_mode[i]; i++) {
        file_mode[i] = tolower(file_mode[i]);
    }

    sprintf(filename, "%s_user_id.txt", file_mode);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening user file for mode %s.\n", mode);
        free(file_mode);
        return 0;
    }

    char admin_id[MAX_ID_LENGTH];
    if (fscanf(file, "%s", admin_id) != 1) {
        printf("Error reading admin user ID from file.\n");
        fclose(file);
        free(file_mode);
        return 0;
    }
    fclose(file);

    if (strcmp(user_id, admin_id) == 0) {
        free(file_mode);
        return 1; // Return 1 if user ID matches
    } else {
        // For other modes, implement proper authentication logic
        sprintf(filename, "%s_users.txt", file_mode);
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening user file for mode %s.\n", mode);
            free(file_mode);
            return 0;
        }

        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            char *token = strtok(line, ", "); // Tokenize line using comma and space as delimiters
            if (token != NULL) {
                if (strcmp(user_id, token) == 0) {
                    token = strtok(NULL, ", "); // Move to next token (password)
                    if (token != NULL && strcmp(password, token) == 0) {
                        fclose(file);
                        free(file_mode);
                        return 1; // Password matches
                    }
                }
            }
        }
        fclose(file);
    }

    free(file_mode);
    return 0; // No match found
}
