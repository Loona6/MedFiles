#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

void med_menu()
{
        int choice;

    do {

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
                break;
            case 3:
                display_doctors();
                break;
            case 4:
                display_appointments();
                break;

            default:
                if (choice < 1 || choice > 5) {
                    printf("Invalid choice. Please try again.\n");
                }
        }
    } while (choice != 5);
}

