#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

void admin() {
    printf("\t\t\t1. Change Password\n");
    printf("\t\t\t2. Add Doctor\n");
    printf("\t\t\t3. Add Staff\n");
    printf("\t\t\t4. Add Ambulance Services\n");
    printf("\t\t\t5. Edit Ambulance Services\n");

    int choice;
    do {
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 6) {
            printf("Invalid mode choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice <1 || choice>6);

    switch (choice) {
        case 2:
            add_doctor();
            break;
        case 3:
            //add_staff();
            break;
        case 5:

            break;
        case 1:
            change_password();
            break;
        case 4:
            //add_ambulance_services();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
