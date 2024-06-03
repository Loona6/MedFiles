
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_LINE_LENGTH 50 // Adjust according to maximum expected line length in the file
#define MAX_USERS 100 // Maximum number of users

int login() {
    // Define variables
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char correct_usernames[MAX_USERS][MAX_USERNAME_LENGTH]; // Store correct usernames read from file
    char correct_passwords[MAX_USERS][MAX_PASSWORD_LENGTH]; // Store correct passwords read from file
    char *token; // Token pointer for strtok
    char line[MAX_LINE_LENGTH]; // Buffer to read each line from the file
    int num_users = 0; // Counter for number of users read from file

    printf("\t\t\t\t\t\tLOGIN to enter MEDFILES\n");
    // Open the file containing correct usernames and passwords
    FILE *file = fopen("credentials.txt", "r");
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
                strcpy(correct_passwords[num_users], token); // Copy the password
                // Remove newline character from password if present
                correct_passwords[num_users][strcspn(correct_passwords[num_users], "\n")] = '\0';
                num_users++; // Increment number of users read
            }
        }
    }

    fclose(file); // Close the file

    // Prompt user for username
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from username if present
    username[strcspn(username, "\n")] = '\0';

    // Prompt user for password
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from password if present
    password[strcspn(password, "\n")] = '\0';

    // Check if the entered username and password match any of the correct ones
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, correct_usernames[i]) == 0 && strcmp(password, correct_passwords[i]) == 0) {
            printf("Login successful! Welcome, %s.\n", username);
            return 1; // Exit the function
        }
    }

    // If no matching username and password are found
    printf("Incorrect username or password.\n");
    return 0;
}
