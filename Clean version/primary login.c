#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void pri_login()
{
    system("color F0");
    char mode[20];
    char choice;

    do
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t\tWelcome to Medfiles\n\n\n");
        printf("\t\t\t Choose Login mode:\n\n");
        printf("\t\t\t1. Admin\n");
        printf("\t\t\t2. Medical staff\n");
        printf("\t\t\t3. Support staff\n");
        printf("\t\t\t4. Exit\n\n");
        printf("\t\t\tEnter your choice number: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');  // Clear input buffer
        system("cls");

        switch (choice)
        {
        case '1':
            strcpy(mode, "Admin");
            if(login(mode)) admin();
            break;
        case '2':
            strcpy(mode, "Medical");
            if(login(mode)) med_menu();
            break;
        case '3':
            strcpy(mode, "Support");
            if(login(mode)) support_menu();
            break;
        case '4':
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        if (choice != '4')
        {
            printf("\n\n\t\t\tPress any key to continue...\n");
            getchar();  // Wait for a key press
            system("cls");  // Clear screen
        }
    }
    while (choice != '4');
}

void admin()
{
    char choice;

    do
    {
        printf("\n\n\n\t\t\t\t\t\tWelcome to Admin\n\n\n");
        printf("\t\t\t1. Change Password\n");
        printf("\t\t\t2. Add Doctor\n");
        printf("\t\t\t3. Add Staff\n");
        printf("\t\t\t4. Add Ambulance Services\n");
        printf("\t\t\t5. Edit Ambulance Services\n");
        printf("\t\t\t6. View Doctor list\n");
        printf("\t\t\t7. View Staff list\n");
        printf("\t\t\t8. View Ambulance list\n");
        printf("\t\t\t9. Return to Main Menu\n\n");

        do
        {
            printf("\t\t\tEnter option: ");
            scanf("%c", &choice);
            while (getchar() != '\n');  // Clear input buffer
            system("cls");

            if (choice < '1' || choice > '9')
            {
                printf("Invalid mode choice. Please enter a number between 1 and 9.\n");
            }
        }
        while (choice < '1' || choice > '9');

        switch (choice)
        {

        case '1':
            // change password

            break;

        case '2':
            // Add Doctor
            add_doctor();
            break;
        case '3':
            // Add Staff
            add_staff();
            break;

        case '4':
            // Add Ambulance services
            add_ambulance();
            break;

        case '5':
            // Edit Ambulance Services
            delete_ambulance();
            break;
        case '6':
            //View doctor list
            display_doctors();
            break;
        case '7':
            //View staff list
            display_staff();

            break;
        case '8':
            //View Ambulance list
            display_ambulance();
            break;
        case '9':
            return;  // Return to Main Menu

        default:
            printf("Invalid choice.\n");
            break;
        }

        if (choice != '9')
        {
            printf("Press any key to continue...\n");
            getchar();  // Wait for a key press
            system("cls");  // Clear screen
        }
    }
    while (choice != '9');
}

void support_menu()
{
    char choice;

    do
    {
        printf("\t\t\t\t\t\tWelcome to Support Staff Menu\n\n\n");
        printf("\t\t\t1. Change password\n");
        printf("\t\t\t2. View Ambulance list\n");
        printf("\t\t\t3. Book Ambulance service\n");
        printf("\t\t\t4. View available Lab tests and prices\n");
        printf("\t\t\t5. View availabe cabin services\n");
        printf("\t\t\t6. Book lab tests/cabin(or both)\n");
        printf("\t\t\t7. Return to Main Menu\n\n");

        do
        {
            printf("Enter option: ");
            scanf("%c ", &choice);
            while (getchar() != '\n');  // Clear input buffer
            system("cls");

            if (choice < '1'|| choice > '7')
            {
                printf("Invalid mode choice. Please enter a number between 1 and 7.\n");
            }
        }
        while (choice < '1' || choice > '7');

        switch (choice)
        {
        case '1':
            // change password

            break;
        case '2':
            //View ambulance list

            break;
        case '3':
            // Book ambulance

            break;
        case '4':
            // view lab tests
            break;
        case '5':
            // view cabin price
            break;
        case '6':
            // book lab test + cabin
            break;
        case '7':
            return;  // Return to Main Menu
        default:
            printf("Invalid choice.\n");
            break;
        }

        if (choice != '7')
        {
            printf("Press any key to continue...\n");
            getchar();  // Wait for a key press
            system("cls");  // Clear screen
        }
    }
    while (choice != '7');
}

void med_menu()
{
    char choice;

    do
    {
        printf("\t\t\t\t\t\tWelcome to Medical Staff Menu\n\n\n");
        printf("\t\t\t1. Add Patient\n");
        printf("\t\t\t2. Book Appointments\n");
        printf("\t\t\t3. View Patient list\n");
        printf("\t\t\t4. View Scheduled Appointments\n");
        printf("\t\t\t5. Search Patient\n");
        printf("\t\t\t6. Add Patient notes\n");
        printf("\t\t\t7. View Patient history\n");
        printf("\t\t\t8. Return to Main Menu\n\n");

        do
        {
            printf("Enter option: ");
            scanf("%c ", &choice);
            while (getchar() != '\n');  // Clear input buffer
            system("cls");

            if (choice < '1' || choice > '7')
            {
                printf("Invalid mode choice. Please enter a number between 1 and 7.\n");
            }
        }
        while (choice < '1' || choice > '7');

        switch (choice)
        {
        case '1':
            // Add Patient

            break;
        case '2':
            // add appointments
            break;
        case '3':
            // view patient
            break;
        case '4':
            //view appointments
            break;
        case '5':
            //search patient
            break;
        case '6':
            //add patient notes
            break;
        case '7':
            //view patient history
            break;
        case '8':
            return;  // Return to Main Menu
        default:
            printf("Invalid choice.\n");
            break;
        }

        if (choice != '8')
        {
            printf("Press any key to continue...\n");
            getchar();  // Wait for a key press
            system("cls");  // Clear screen
        }
    }
    while (choice != '8');
}