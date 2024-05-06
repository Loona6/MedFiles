#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

void pri_login()
{
    char mode[20];
    int choice;
        printf("\t\t\t\t\t\tWelcome to Medfiles\n\n\n");
        printf("\t\t\t Choose Login mode:\n");
        printf("\t\t\t1. Admin\n");
        printf("\t\t\t2. Medical staff\n");
        printf("\t\t\t3. Support staff\n");
        printf("\t\t\t4. Exit\n");
        printf("\t\t\tEnter your choice number (Don't input anything other than number) : ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                strcpy(mode, "Admin");
                admin_pass(mode);
                break;
            case 2:
              strcpy(mode, "Medical staff");
              //login();
              med_menu();

                break;
            case 3:
                strcpy(mode, "Support staff");
                //login();
                support_menu();
                break;

            default:
                if (choice < 1 || choice > 3) {
                    printf("Invalid choice. Please try again.\n");
                }
        }
}
