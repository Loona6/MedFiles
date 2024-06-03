#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_LINE_LENGTH 50 // Adjust according to maximum expected line length in the file

void admin_pass();
int check_credentials(const char *user_id, const char *password);

void admin_pass() {
    char user_id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your user ID: ");
    fgets(user_id, MAX_ID_LENGTH, stdin);
    user_id[strcspn(user_id, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (check_credentials(user_id, password)) {
        printf("Login successful!\n");
        // Add the function or actions to be taken after successful login
    } else {
        printf("Invalid user ID or password.\n");
    }
}

int check_credentials(const char *user_id, const char *password) {
    FILE *file;
    char line[MAX_LINE_LENGTH]; // Buffer to read each line from the file
    const char *filename = "admin_user_id.txt";

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening user file %s.\n", filename);
        return 0;
    }

    // Read each line and check credentials
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ","); // Tokenize line using comma as a delimiter
        if (token != NULL && strcmp(user_id, token) == 0) {
            token = strtok(NULL, ",");
            if (token != NULL && strcmp(password, token) == 0) {
                fclose(file);
                return 1; // User ID and password match
            }
        }
    }
    fclose(file);

    return 0; // No match found
}
