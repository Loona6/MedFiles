
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <conio.h> // Include for getch()
#include "sha256.h"

#define HASH_LENGTH 64 // SHA-256 produces 64-character hash
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 65
#define MAX_LINE_LENGTH 100 // Adjust according to your maximum expected line length
#define MAX_USERS 100 // Maximum number of users

char logged_in_username[MAX_USERNAME_LENGTH];

void hashPassword(const char *password, char *hash) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (const uint8_t *)password, strlen(password));
    sha256_final(&ctx, (uint8_t *)hash);

    // Convert binary hash to hexadecimal string
    char hex_hash[2 * 32 + 1];
    for (int i = 0; i < 32; i++) {
        sprintf(hex_hash + 2 * i, "%02x", (uint8_t)hash[i]);
    }
    strcpy(hash, hex_hash);
}

int verifyPassword(const char *input_password, const char *stored_hash) {
    char input_hash[HASH_LENGTH + 1]; // Room for hexadecimal hash + null terminator

    hashPassword(input_password, input_hash);
    //printf("%s %s",input_hash, stored_hash);
    return strcmp(input_hash, stored_hash) == 0;
}

void getPassword(char *password) {
    int index = 0;
    char ch;
    while (1) {
        ch = getch(); // read a character without echoing it
        if (ch == '\r' || ch == '\n') { // 'Enter' key, end input
            password[index] = '\0'; // null-terminate the string
            break;
        } else if (ch == '\b') { // 'Backspace' key, delete the last character
            if (index > 0) {
                index--;
                printf("\b \b"); // move cursor back, overwrite with space, move cursor back again
            }
        } else {
            password[index] = ch;
            index++;
            printf("*"); // display an asterisk
        }
    }
    printf("\n");
}

int login(const char *mode) {
    // Define variables
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char correct_usernames[MAX_USERS][MAX_USERNAME_LENGTH]; // Store correct usernames read from file
    char correct_password_hashes[MAX_USERS][HASH_LENGTH + 1]; // Store hashed passwords read from file
    char *token; // Token pointer for strtok
    char line[MAX_LINE_LENGTH]; // Buffer to read each line from the file
    int num_users = 0; // Counter for number of users read from file

    printf("\t\t\t\t\t\tLOGIN to enter MEDFILES\n");

    // Open the file containing correct usernames and hashed passwords
    FILE *file;
    if (strcmp(mode, "Admin") == 0) {
        file = fopen("Admin_credentials.txt", "r");
    } else if (strcmp(mode, "Medical") == 0) {
        file = fopen("Medical_credentials.txt", "r");
    } else if (strcmp(mode, "Support") == 0) {
        file = fopen("Support_credentials.txt", "r");
    } else {
        printf("Invalid mode.\n");
        return 0;
    }

    if (file == NULL) {
        printf("Error opening credentials file.\n");
        return 0;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL && num_users < MAX_USERS) {
        // Tokenize the line based on comma
        token = strtok(line, ",");
        if (token != NULL) {
            strcpy(correct_usernames[num_users], token); // Copy the username
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(correct_password_hashes[num_users], token); // Copy the hashed password
                correct_password_hashes[num_users][strcspn(correct_password_hashes[num_users], "\n")] = '\0'; // Remove newline character
                num_users++; // Increment number of users read
            }
        }
    }

    fclose(file); // Close the file

    // Prompt user for username
    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
    }
    printf("Enter password: ");
    // Prompt user for password
    getPassword(password);

    // Check if the entered username and password match any of the correct ones
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, correct_usernames[i]) == 0 && verifyPassword(password, correct_password_hashes[i])) {
            printf("Login successful! Welcome, %s.\n", username);
            strcpy(logged_in_username, username);
            printf("Press Enter to continue...");
            getchar(); // Clear input buffer
            getchar(); // Wait for Enter key

            clear_screen(); // Clear screen after operation
            return 1; // Exit the function
        }
    }

    // If no matching username and password are found
    printf("Incorrect username or password.\n");
    return 0;
}
void change_password(const char *mode, const char *logged_in_username, const char *target_username) {
    // Define variables
    char new_password[MAX_PASSWORD_LENGTH];
    char line[MAX_LINE_LENGTH]; // Buffer to read each line from the file
    int user_found = 0; // Flag to track if the target username was found

    // Open the file containing correct usernames and hashed passwords
    FILE *file;
    if (strcmp(mode, "Admin") == 0) {
        file = fopen("Admin_credentials.txt", "r");
    } else if (strcmp(mode, "Medical") == 0) {
        file = fopen("Medical_credentials.txt", "r");
    } else if (strcmp(mode, "Support") == 0) {
        file = fopen("Support_credentials.txt", "r");
    } else {
        printf("Invalid mode.\n");
        return;
    }

    if (file == NULL) {
        printf("Error opening credentials file.\n");
        return;
    }

    // Create a temporary file to store updated content
    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        // Find newline character if exists
        char *newline_pos = strchr(line, '\n');
        if (newline_pos != NULL) {
            // Found newline character, terminate the string there
            *newline_pos = '\0';
        }

        // Tokenize the line to extract username and hashed password
        char *line_copy = strdup(line);
        char *token = strtok(line_copy, ",");
        if (token != NULL && strcmp(token, target_username) == 0) {
            user_found = 1; // Set the flag to indicate that the user was found
            // If the username matches the target username, prompt the user to enter a new password
            if (strcmp(logged_in_username, target_username) != 0) {
                // If the logged-in username does not match the target username, display an error message
                printf("You are not authorized to change the password for %s.\n", target_username);
                // Write the original line to the temporary file
                fprintf(temp_file, "%s\n", line); // Write original line as-is
            } else {
                // Prompt the user to enter a new password
                printf("Enter new password for %s: ", target_username);
                getPassword(new_password);

                // Hash the new password
                char new_password_hash[HASH_LENGTH + 1];
                hashPassword(new_password, new_password_hash);

                // Write the updated line to the temporary file
                fprintf(temp_file, "%s,%s\n", target_username, new_password_hash);
                printf("Password changed successfully for user %s.\n", target_username);
            }
        } else {
            // Write the original line to the temporary file
            fprintf(temp_file, "%s\n", line); // Write original line as-is
        }

        // Free memory allocated by strdup
        free(line_copy);
    }

    // Close files
    fclose(file);
    fclose(temp_file);

    // Check if the target username was not found
    if (!user_found) {
        printf("User %s does not exist.\n", target_username);
        // Remove the temporary file as no changes were made
        remove("temp.txt");
    } else {
        // Replace the original file with the temporary file
        if (strcmp(mode, "Admin") == 0) {
            remove("Admin_credentials.txt"); // Remove original file
            rename("temp.txt", "Admin_credentials.txt"); // Rename temporary file
        } else if (strcmp(mode, "Medical") == 0) {
            remove("Medical_credentials.txt"); // Remove original file
            rename("temp.txt", "Medical_credentials.txt"); // Rename temporary file
        } else if (strcmp(mode, "Support") == 0) {
            remove("Support_credentials.txt"); // Remove original file
            rename("temp.txt", "Support_credentials.txt"); // Rename temporary file
        }
    }
}
const char* namesender() {
    return logged_in_username;
}
