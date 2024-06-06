#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <stdlib.h>
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
char username[MAX_USERNAME_LENGTH];
char docname[MAX_USERNAME_LENGTH];
char mode[20];



void pri_login()
{
    system("color F0");

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
            int verify=login(mode);
            if(verify) admin();
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
            printf("Enter username: ");
            fgets(username, MAX_USERNAME_LENGTH, stdin);

            // Clear input buffer
            if (username[strlen(username) - 1] == '\n')
                username[strlen(username) - 1] = '\0';
            else
                while (getchar() != '\n');  // Clear input buffer if necessary

            change_password(mode,namesender(),username);
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
        printf("\n\n\n\t\t\t\t\t\tWelcome to Support Staff Menu\n\n\n");
        printf("\t\t\t1. Change password\n");
        printf("\t\t\t2. View Ambulance list\n");
        printf("\t\t\t3. Book Ambulance service\n");
        printf("\t\t\t4. Unbook Ambulance service\n");
        printf("\t\t\t5. View and book lab tests\n");
        printf("\t\t\t6. View and book cabin services\n");
        printf("\t\t\t7. Book appointment\n");
        printf("\t\t\t8. View appointment\n");
        printf("\t\t\t9. Clear appointment\n");
        printf("\t\t\t10. View billing history\n");
        printf("\t\t\t11. Return to Main Menu\n\n");

        do
        {
            printf("\t\t\tEnter option: ");
            scanf("%c", &choice);
            while (getchar() != '\n');  // Clear input buffer
            system("cls");

            if (choice < '1'|| choice > '11')
            {
                printf("Invalid mode choice. Please enter a number between 1 and 9.\n");
            }
        }
        while (choice < '1' || choice > '11');
        switch (choice){
        case '1':
             // change password
            printf("Enter username: ");
            fgets(username, MAX_USERNAME_LENGTH, stdin);

            // Clear input buffer
            if (username[strlen(username) - 1] == '\n')
                username[strlen(username) - 1] = '\0';
            else
                while (getchar() != '\n');  // Clear input buffer if necessary

            change_password(mode,namesender(),username);
            break;
        case '2':
            //View ambulance list
            display_ambulance();
            break;
        case '3':
            // Book ambulance
            //book_ambulance();
            break;
        case '4':
            //unbook_ambulance();
            break;
        case '5':
            //mainMenuforlabtest();
            break;
        case '10':
            // book lab test + cabin
            bookTest();
            break;
        case '9':
            printf("Enter doctor's name: ");
            fgets(docname, MAX_USERNAME_LENGTH, stdin);

            // Remove newline character from the doctor's name
            docname[strcspn(docname, "\n")] = '\0';
            clear_appointments(docname);
            break;
        case '8':
            // view appointment
            printf("Enter doctor's name: ");
            fgets(docname, MAX_USERNAME_LENGTH, stdin);

            // Remove newline character from the doctor's name
            docname[strcspn(docname, "\n")] = '\0';

            display_appointments(docname);
            break;
        case '7':
            // book appointment
            printf("Enter doctor's name: ");
            fgets(docname, MAX_USERNAME_LENGTH, stdin);

            // Remove newline character from the doctor's name
            docname[strcspn(docname, "\n")] = '\0';

            add_appointment(docname);
            break;
        case '6':
            //mainMenuforcabin();
            break;
        case '11':
            return;  // Return to Main Menu

        default:
            printf("Invalid choice.\n");
            break;
        }

        if (choice != '11')
        {
            printf("Press any key to continue...\n");
            getchar();  // Wait for a key press
            system("cls");  // Clear screen
        }
    }
    while (choice != '11');
}

void med_menu()
{
    char choice;

    do
    {
        printf("\t\t\t\t\t\tWelcome to Medical Staff Menu\n\n\n");
        printf("\t\t\t1. Change password\n");
        printf("\t\t\t2. Add Patient\n");
        printf("\t\t\t3. View Patient list\n");
        printf("\t\t\t4. View Scheduled Appointments\n");
        printf("\t\t\t5. Search Patient\n");
        printf("\t\t\t6. Add Patient notes\n");
        printf("\t\t\t7. Return to Main Menu\n\n");

        do
        {
            printf("Enter option: ");
            scanf("%c", &choice);
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
        case '2':
            // Add Patient
            add_patient();
            break;
        case '1':
             // change password
            printf("Enter username: ");
            fgets(username, MAX_USERNAME_LENGTH, stdin);

            // Clear input buffer
            if (username[strlen(username) - 1] == '\n')
                username[strlen(username) - 1] = '\0';
            else
                while (getchar() != '\n');  // Clear input buffer if necessary

            change_password(mode,namesender(),username);
            break;
        case '3':
            {
                // View Patients
                int sort_choice;
                printf("View patients sorted by:\n");
                printf("1. Name\n");
                printf("2. Date\n");
                printf("Enter your choice: \n\n");
                scanf("%d", &sort_choice);
                while (sort_choice < 1 || sort_choice > 2) {
                    printf("Invalid choice. Please enter 1 for Name or 2 for Date: ");
                    scanf("%d", &sort_choice);
                }
                display_patients(sort_choice);
                break;
            }
        case '4':
            //view appointments
            display_appointments(namesender());
            break;
        case '5':
            //search patient
            search_patient();
            break;
        case '6':
            //add patient notes
            Pdf();
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
