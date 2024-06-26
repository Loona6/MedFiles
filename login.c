
//#include <stdio.h>
//#include <string.h>
//
//#define MAX_USERNAME_LENGTH 20
//#define MAX_PASSWORD_LENGTH 20
//#define MAX_LINE_LENGTH 50 // Adjust according to maximum expected line length in the file
//#define MAX_USERS 100 // Maximum number of users
//char logged_in_username[MAX_USERNAME_LENGTH];
//
//int login(const char *mode) {
//    // Define variables
//    char username[MAX_USERNAME_LENGTH];
//    char password[MAX_PASSWORD_LENGTH];
//    char correct_usernames[MAX_USERS][MAX_USERNAME_LENGTH]; // Store correct usernames read from file
//    char correct_passwords[MAX_USERS][MAX_PASSWORD_LENGTH]; // Store correct passwords read from file
//    char *token; // Token pointer for strtok
//    char line[MAX_LINE_LENGTH]; // Buffer to read each line from the file
//    int num_users = 0; // Counter for number of users read from file
//
//    printf("\t\t\t\t\t\tLOGIN to enter MEDFILES\n");
//    // Open the file containing correct usernames and passwords
//    FILE *file;
//    if (strcmp(mode, "Admin") == 0) {
//        file = fopen("Admin_credentials.txt", "r");
//    } else if (strcmp(mode, "Medical") == 0) {
//        file = fopen("Medical_credentials.txt", "r");
//    } else if (strcmp(mode, "Support") == 0) {
//        file = fopen("Support_credentials.txt", "r");
//    } else {
//        printf("Invalid mode.\n");
//        return 0;
//    }
//
//    if (file == NULL) {
//        printf("Error opening credentials file.\n");
//        return 0;
//    }
//
//    // Read each line from the file
//    while (fgets(line, sizeof(line), file) != NULL && num_users < MAX_USERS) {
//        // Tokenize the line based on comma
//        token = strtok(line, ",");
//        if (token != NULL) {
//            strcpy(correct_usernames[num_users], token); // Copy the username
//            token = strtok(NULL, ",");
//            if (token != NULL) {
//                strcpy(correct_passwords[num_users], token); // Copy the password
//                // Remove newline character from password if present
//                correct_passwords[num_users][strcspn(correct_passwords[num_users], "\n")] = '\0';
//                num_users++; // Increment number of users read
//            }
//        }
//    }
//
//    fclose(file); // Close the file
//
//    // Prompt user for username
//    printf("Enter username: ");
//    fgets(username, MAX_USERNAME_LENGTH, stdin);
//    // Remove newline character from username if present
//    username[strcspn(username, "\n")] = '\0';
//
//    // Prompt user for password
//    printf("Enter password: ");
//    fgets(password, MAX_PASSWORD_LENGTH, stdin);
//    // Remove newline character from password if present
//    password[strcspn(password, "\n")] = '\0';
//
//    // Check if the entered username and password match any of the correct ones
//    for (int i = 0; i < num_users; i++) {
//        if (strcmp(username, correct_usernames[i]) == 0 && strcmp(password, correct_passwords[i]) == 0) {
//            printf("Login successful! Welcome, %s.\n", username);
//            strcpy(logged_in_username, username);
//            return 1; // Exit the function
//        }
//    }
//
//    // If no matching username and password are found
//    printf("Incorrect username or password.\n");
//    return 0;
//}
//const char* namesender(){
//
//    return logged_in_username;
//
//}
//
//void change_password(const char *mode, const char *logged_in_username, const char *target_username) {
//    // Define variables
//    char new_password[MAX_PASSWORD_LENGTH];
//    char line[MAX_LINE_LENGTH]; // Buffer to read each line from the file
//
//    // Open the file containing correct usernames and passwords
//    FILE *file;
//    if (strcmp(mode, "Admin") == 0) {
//        file = fopen("Admin_credentials.txt", "r");
//    } else if (strcmp(mode, "Medical") == 0) {
//        file = fopen("Medical_credentials.txt", "r");
//    } else if (strcmp(mode, "Support") == 0) {
//        file = fopen("Support_credentials.txt", "r");
//    } else {
//        printf("Invalid mode.\n");
//        return;
//    }
//
//    if (file == NULL) {
//        printf("Error opening credentials file.\n");
//        return;
//    }
//
//    // Create a temporary file to store updated content
//    FILE *temp_file = fopen("temp.txt", "w");
//    if (temp_file == NULL) {
//        printf("Error creating temporary file.\n");
//        fclose(file);
//        return;
//    }
//
//    // Read each line from the file
//    while (fgets(line, sizeof(line), file) != NULL) {
//        // Copy the line to maintain original content
//        char *line_copy = strdup(line);
//
//        // Tokenize the line to extract username and password
//        char *token = strtok(line_copy, ",");
//        if (token != NULL && strcmp(token, target_username) == 0) {
//            // If the username matches the target username, prompt the user to enter a new password
//            if (strcmp(logged_in_username, target_username) != 0) {
//                // If the logged-in username does not match the target username, display an error message
//                printf("You are not authorized to change the password for %s.\n", target_username);
//                // Write the original line to the temporary file
//                fputs(line, temp_file);
//            } else {
//                // Prompt the user to enter a new password
//                printf("Enter new password for %s: ", target_username);
//                fgets(new_password, MAX_PASSWORD_LENGTH, stdin);
//                // Remove newline character from password if present
//                new_password[strcspn(new_password, "\n")] = '\0';
//                // Write the new password to the temporary file
//                fprintf(temp_file, "%s,%s\n", target_username, new_password);
//                printf("Password changed successfully for user %s.\n", target_username);
//            }
//        } else {
//            // Write the original line to the temporary file
//            fputs(line, temp_file);
//        }
//
//        // Free memory allocated by strdup
//        free(line_copy);
//    }
//
//    // Close files
//    fclose(file);
//    fclose(temp_file);
//
//    // Replace the original file with the temporary file
//    remove("Admin_credentials.txt"); // Remove original file
//    rename("temp.txt", "Admin_credentials.txt"); // Rename temporary file
//}
