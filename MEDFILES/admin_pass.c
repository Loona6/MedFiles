#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

#define MAX_ID_LENGTH 20

void admin_pass(char *mode)
{
    char user_id[MAX_ID_LENGTH];
    printf("Enter your user ID: ");
    scanf("%s", user_id);

    if (check_credentials(mode, user_id)) {
        display_options(mode);
    }
    else {
        printf("Invalid user ID or mode.\n");

    }
}

int check_credentials(char *mode, char *user_id) {
    if (strcmp(mode, "Admin") == 0) {
        // Check if the mode is "Admin"
        FILE *file = fopen("admin_user_id.txt", "r");
        if (file == NULL) {
            printf("Error opening admin user ID file.\n");
            return 0;
        }

        char admin_id[MAX_ID_LENGTH];
        if (fscanf(file, "%s", admin_id) != 1) {
            printf("Error reading admin user ID from file.\n");
            fclose(file);
            return 0;
        }

        fclose(file);

        if (strcmp(user_id, admin_id) == 0) {
            return 1; // Return 1 if user ID matches
        }
    } else {
        // For other modes, implement proper authentication logic
        char filename[20];
        sprintf(filename, "%s_users.txt", mode);
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening user file for mode %s.\n", mode);
            return 0;
        }

        char line[100];
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, user_id) != NULL) {
                fclose(file);
                return 1;
            }
        }

        fclose(file);
    }

    return 0;
}

void change_password() {
    char new_password[MAX_ID_LENGTH];

    printf("Enter new password for admin: ");
    scanf("%s", new_password);

    // Open the file in write mode
    FILE *file = fopen("admin_user_id.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write the new password to the file
    fprintf(file, "%s", new_password);

    // Close the file
    fclose(file);

    printf("Admin password changed successfully.\n");
}


// Function to display options based on mode
void display_options(char *mode) {
    if (strcmp(mode, "Admin") == 0) {
        printf("\t\t\t\t\t\tWelcome to Medfiles\n\n\n");
        printf("\t\t\t\t\Welcome Admin! You have access to administrative options.\n\n");
        admin();
    } else if (strcmp(mode, "Med staff") == 0) {
        printf("\t\t\t\t\t\Welcome Medical Staff! You have access to medical options.\n");

    } else if (strcmp(mode, "Support staff") == 0) {
        printf("\t\t\t\t\t\Welcome Support Staff! You have access to support options.\n");
        // Add support options here
    } else {
        printf("Invalid mode.\n");
    }
}
