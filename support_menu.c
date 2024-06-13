#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

void support_menu()
{
    int choice;

    do
    {
        printf("\t\t\t\t\t\tWelcome to Support Staff Menu\n\n\n");
        printf("\t\t\t1. Add Appointment\n");
        printf("\t\t\t2. Display Doctors\n");
        printf("\t\t\t3. Display Appointments\n");
        printf("\t\t\t4. Book Ambulance Service\n");
        printf("\t\t\t5. Book lab tests\n");
        printf("\t\t\t6. Billing and invoice\n");
//        printf("\t\t\t7. Return to login mode\n");
//        printf("\t\t\t8. Return to main menu\n");
        printf("\t\t\t7. Exit\n");
        printf("\t\t\tEnter your choice number (Don't input anything other than number) : ");
        scanf("%d", &choice);
        system("cls");

        switch (choice)
        {

        case 1:
            add_appointment();
            break;

        case 2:
            display_doctors();
            break;
        case 3:
            display_appointments();
            break;
//        case 7:
//            pri_login();
//            break;
//        case 8:
//            support_menu();
//            break;



        default:
            if (choice < 1 || choice > 7)
            {
                printf("Invalid choice. Please try again.\n");
            }
        }
    }
    while (choice != 7);
}
