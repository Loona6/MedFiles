#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


 void login()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char correct_username[] = "user";
    char correct_password[] = "password";

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
        system("cls");
        printf("\t\t\t\t\t\t Login successful!!\n");
    }
    else
    {
        printf("Wrong password. Please try again\n");
        login();
        system("cls");

    }

}
