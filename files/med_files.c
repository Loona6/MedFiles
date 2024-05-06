#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#define MAX_AMBULANCES 3
#define MAX_ID_LENGTH 20
int value;

void add_doctor() {
    char name_1[500], name_2[500];
    char user_id[MAX_ID_LENGTH];

    printf("Enter doctor's name\nFirst name:");
    scanf("%s", name_1);
    printf("Last name:");
    scanf("%s", name_2);
    printf("Enter doctor's user ID: ");
    scanf("%s", user_id);

      // Open the CSV file in append mode
    FILE *file = fopen("doctors.csv", "a");
    if (file == NULL) {
        // If file doesn't exist, create a new file
        file = fopen("doctors.csv", "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }
        // Write header to the file
        fprintf(file, "First Name,Last Name,User ID\n");
    }

    // Write doctor's information to the file
    fprintf(file, "%s,%s,%s\n", name_1,name_2,user_id);

    // Close the file
    fclose(file);

    printf("Doctor %s %s added successfully with user ID %s.\n", name_1,name_2, user_id);
}


// Function to add a staff member
void add_staff() {
   char name_1[500], name_2[500];
    char user_id[MAX_ID_LENGTH];

   printf("Enter Staff member's name\nFirst name:");
    scanf("%s", name_1);
    printf("Last name:");
    scanf("%s", name_2);
    printf("Enter Staff member's user ID: ");
    scanf("%s", user_id);

    // Open the CSV file in append mode
    FILE *file = fopen("staff.csv", "a");
    if (file == NULL) {
        // If file doesn't exist, create a new file
        file = fopen("staff.csv", "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }
        // Write header to the file
        fprintf(file, "First Name,Last Name,User ID\n");
    }

    // Write doctor's information to the file
    fprintf(file, "%s,%s,%s\n", name_1,name_2,user_id);

    // Close the file
    fclose(file);
    printf("Staff member %s %s added successfully with user ID %s.\n",name_1,name_2, user_id);
}


typedef struct {
    char number[MAX_ID_LENGTH];
    char contact[MAX_ID_LENGTH];
    char status[20]; // "Booked" or "Unbooked"
    char booked_by[MAX_ID_LENGTH];
} Ambulance;

Ambulance ambulances[MAX_AMBULANCES];

void add_ambulance_services() {
        printf("Enter ambulance details:\n");
        for (int i = 0; i < MAX_AMBULANCES; i++) {
            printf("Enter ambulance number for Ambulance %d: ", i + 1);
            scanf("%s", ambulances[i].number);
            printf("Enter contact number for Ambulance %d: ", i + 1);
            scanf("%s", ambulances[i].contact);
            strcpy(ambulances[i].status, "Unbooked");
            strcpy(ambulances[i].booked_by, "");
        }

        FILE *file = fopen("ambulance_services.csv", "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }

        // Write ambulance details to the file
        fprintf(file, "Number,Contact,Status,Booked By\n");
        for (int i = 0; i < MAX_AMBULANCES; i++) {
            fprintf(file, "%s,%s,%s,%s\n", ambulances[i].number, ambulances[i].contact, ambulances[i].status, ambulances[i].booked_by);
        }

        fclose(file);
        printf("Ambulance services added successfully.\n");

    printf("Continue? Yes(1)/No(0)\n");
    scanf("%d", &value);
    admin();
}

void book_ambulance() {
    int value;
    char contact[MAX_ID_LENGTH];
    printf("Enter your contact for booking: ");
    scanf("%s", contact);

    // Read ambulance details from the CSV file
    FILE *file = fopen("ambulance_services.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Skip the header line
    char line[100];
    fgets(line, sizeof(line), file);

    // Find an unbooked ambulance
    int unbooked_found = -1;
    printf("Available Ambulances:\n");
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        char number[MAX_ID_LENGTH], status[20], booked_by[MAX_ID_LENGTH];

        // Tokenize the line based on commas
        char *token = strtok(line, ",");
        strcpy(number, token); // First token is the number

        token = strtok(NULL, ",");
        // Second token is not needed, it's the contact

        token = strtok(NULL, ",");
        strcpy(status, token); // Third token is the status

        token = strtok(NULL, ",");
        strcpy(booked_by, token); // Fourth token is the booked_by

        if (strcmp(status, "Unbooked") == 0) {
            unbooked_found = index;
            break; // Found an unbooked ambulance, no need to continue searching
        }
        index++;
    }

    fclose(file);

    if (unbooked_found == -1) {
        printf("No unbooked ambulances available.\n");
        return;
    }

    // Update the status and booked_by fields of the unbooked ambulance
    FILE *update_file = fopen("ambulance_services.csv", "r+");
    if (update_file == NULL) {
        printf("Error opening file for updating.\n");
        return;
    }

    // Move the file pointer to the beginning of the line for the unbooked ambulance
    fseek(update_file, 0, SEEK_SET);
    for (int i = 0; i <= unbooked_found; i++) {
        fgets(line, sizeof(line), update_file);
    }

    // Update the status and booked_by fields
    fseek(update_file, -strlen(line), SEEK_CUR);
    fprintf(update_file, "%s,%s,Booked,%s\n", strtok(line, ","), strtok(NULL, ","), contact);

    fclose(update_file);

    printf("Ambulance booked successfully.\n");

    printf("Continue? Yes(1)/No(0)\n");
    scanf("%d", &value);
    if (value==1) admin();
}


void change_password() {
    char new_password[MAX_ID_LENGTH];

    printf("Enter new password for admin: ");
    scanf("%s", new_password);

    // Open the file in write mode
    FILE *file = fopen("admin_user_id.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write the new password to the file
    fprintf(file, "%s", new_password);

    // Close the file
    fclose(file);

    printf("Admin password changed successfully.\n");
}




void admin() {
    printf("1. Change Password\n");
    printf("2. Add Doctor\n");
    printf("3. Add Staff\n");
    printf("4. Add Ambulance Services\n");
    printf("5. Edit Ambulance Services\n");

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
            add_staff();
            break;
        case 5:

            break;
        case 1:
            change_password();
            break;
        case 4:
            add_ambulance_services();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

void med() {
    printf("1. My profile\n");
    printf("2. My patients\n");

    int choice;
    do {
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 2) {
            printf("Invalid mode choice. Please enter a number between 1 and 2.\n");
        }
    } while (choice <1 || choice>2);

    switch (choice) {
        case 1:
            //profile_med();
            break;
        case 2:
            //patient();
        default:
            printf("Invalid choice.\n");
            break;
    }
}


























int check_credentials(char *mode, char *user_id) {
    if (strcmp(mode, "Admin") == 0) {
        // Check if the mode is "Admin"
        FILE *file = fopen("admin_user_id.txt", "r");
        if (file == NULL) {
            printf("Error opening admin user ID file.\n");
            return 0;
        }

        char admin_id[MAX_ID_LENGTH];
        if (fscanf(file, "%s", admin_id) != 1) {
            printf("Error reading admin user ID from file.\n");
            fclose(file);
            return 0;
        }

        fclose(file);

        if (strcmp(user_id, admin_id) == 0) {
            return 1; // Return 1 if user ID matches
        }
    } else {
        // For other modes, implement proper authentication logic
        char filename[20];
        sprintf(filename, "%s_users.txt", mode);
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening user file for mode %s.\n", mode);
            return 0;
        }

        char line[100];
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, user_id) != NULL) {
                fclose(file);
                return 1;
            }
        }

        fclose(file);
    }

    return 0;
}



// Function to display options based on mode
void display_options(char *mode) {
    if (strcmp(mode, "Admin") == 0) {
        printf("\t\t\t\t\t\Welcome Admin! You have access to administrative options.\n");
        admin();
    } else if (strcmp(mode, "Med staff") == 0) {
        printf("\t\t\t\t\t\Welcome Medical Staff! You have access to medical options.\n");
        // Add medical options here
    } else if (strcmp(mode, "Support staff") == 0) {
        printf("\t\t\t\t\t\Welcome Support Staff! You have access to support options.\n");
        // Add support options here
    } else {
        printf("Invalid mode.\n");
    }
}

int main() {
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
                break;
            case 2:
              strcpy(mode, "Medical staff");
                break;
            case 3:
                strcpy(mode, "Support staff");
                break;

            default:
                if (choice < 1 || choice > 3) {
                    printf("Invalid choice. Please try again.\n");
                }
        }

    char user_id[MAX_ID_LENGTH];
    printf("Enter your user ID: ");
    scanf("%s", user_id);

    if (check_credentials(mode, user_id)) {
        display_options(mode);
    }
    else {
        printf("Invalid user ID or mode.\n");
         printf("Continue?Yes(1)/No(0)\n");
        scanf("%d", &value);
        printf("\n");
        if(value) main();
    }

    return 0;
}
