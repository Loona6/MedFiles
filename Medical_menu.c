#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

void med_menu()
{
        int choice;

    do {
        printf("\t\t\t\t\t\tWelcome to Medical Staff Menu\n\n\n");
        printf("\t\t\t1. Add Patient\n");
        printf("\t\t\t2. Display Patients\n");
        printf("\t\t\t3. Display Doctors\n");
        printf("\t\t\t4. Display Appointments\n");
        printf("\t\t\t5. Exit\n");
        printf("\t\t\tEnter your choice number (Don't input anything other than number) : ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                add_patient();

                break;
            case 2:
                display_patients();
                med_menu();
                system("cls");
                //med_menu();
                break;
            case 3:
                display_doctors();
                med_menu();
                system("cls");
                break;
            case 4:
                display_appointments();
                med_menu();
                system("cls");
                break;

            default:
                if (choice < 1 || choice > 5) {
                    printf("Invalid choice. Please try again.\n");
                }
        }
    } while (choice != 5);
}

