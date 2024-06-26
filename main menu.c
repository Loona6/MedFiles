#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

void Main_menu() {
    int choice;

    do {
        printf("\t\t\t\t\t\tWelcome to Medfiles\n\n\n");
        printf("\t\t\t1. Add Patient\n");
        printf("\t\t\t2. Add Doctor\n");
        printf("\t\t\t3. Add Appointment\n");
        printf("\t\t\t4. Display Patients\n");
        printf("\t\t\t5. Display Doctors\n");
        printf("\t\t\t6. Display Appointments\n");
        printf("\t\t\t7. Ambulance Service\n");
        printf("\t\t\t8. Book lab tests\n");
        printf("\t\t\t9. Billing and invoice\n");
        printf("\t\t\t10. Exit\n");
        printf("\t\t\tEnter your choice number (Don't input anything other than number) : ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                add_patient();
                break;
            case 2:
             add_doctor();
                break;
            case 3:
                add_appointment();
                break;
            case 4:
                display_patients();
                break;
            case 5:
                display_doctors();
                break;
            case 6:
                display_doctors();
                break;


            default:
                if (choice < 1 || choice > 10) {
                    printf("Invalid choice. Please try again.\n");
                }
        }
    } while (choice != 10);
}
