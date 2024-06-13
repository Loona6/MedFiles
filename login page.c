#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

   void login(){
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char correct_username[] = "user";
    char correct_password[] = "pass";

    printf("\t\t\t\t\t\tLOGIN to enter MEDFILES\n");

    // Prompt user for username
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from username if present
    username[strcspn(username, "\n")] = 0;

    // Prompt user for password
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from password if present
    password[strcspn(password, "\n")] = 0;

    // Check if the entered username and password match
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0)
    {
        printf("Login successful!\n");
        system("cls");
    }
    else{
        printf("wrong password, Please enter the correct one");
        system("cls");
        printf("\n");
        printf("Your password/username was wrong\n");
        login();
    }

   }
