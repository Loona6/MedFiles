#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#define MAX_AMBULANCES 15
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
    char status[20]; // "Booked" or "Unbooked"
    char booked_by[MAX_ID_LENGTH];
} Ambulance;




Ambulance ambulances[MAX_AMBULANCES];

// Function to add ambulance services
void add_ambulance_services() {
    FILE *file = fopen("ambulance_services.csv", "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }

    // Initialize ambulances
    for (int i = 0; i < MAX_AMBULANCES; i++) {
        sprintf(ambulances[i].number, "Ambulance %d", i + 1);
        strcpy(ambulances[i].status, "Unbooked");
        strcpy(ambulances[i].booked_by, "");
        fprintf(file, "%s,%s,%s\n", ambulances[i].number, ambulances[i].status, ambulances[i].booked_by);
    }

    fclose(file);
    printf("Ambulance services added successfully.\n");
    printf("Continue?Yes(1)/No(0)");
    scanf("%d", &value);
    if(value) admin();
}

// Function to book an ambulance
void book_ambulance() {
    char contact[MAX_ID_LENGTH];
    printf("Enter your contact for booking: ");
    scanf("%s", contact);

    // Find an unbooked ambulance
    int unbooked_index = -1;
    for (int i = 0; i < MAX_AMBULANCES; i++) {
        if (strcmp(ambulances[i].status, "Unbooked") == 0) {
            unbooked_index = i;
            break;
        }
    }

    if (unbooked_index != -1) {
        strcpy(ambulances[unbooked_index].status, "Booked");
        strcpy(ambulances[unbooked_index].booked_by, contact);

        FILE *file = fopen("ambulance_services.csv", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        for (int i = 0; i < MAX_AMBULANCES; i++) {
            fprintf(file, "%s,%s,%s\n", ambulances[i].number, ambulances[i].status, ambulances[i].booked_by);
        }

        fclose(file);

        printf("Ambulance %s booked successfully by %s.\n", ambulances[unbooked_index].number, contact);
    } else {
        printf("No unbooked ambulances available.\n");
    }
}


// Function to change admin password
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
    printf("Continue?Yes(1)/No(0)");
    scanf("%d", &value);
    if(value) admin();
}


void admin() {
    printf("1. Add Doctor\n");
    printf("2. Add Staff\n");
    printf("3. Edit Ambulance Services\n");
    printf("4. Change Password\n");
    printf("5. Add Ambulance Services\n");
    printf("6. Book Ambulance\n");

    int choice;
    do {
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 6) {
            printf("Invalid mode choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice <1 || choice>6);

    switch (choice) {
        case 1:
            add_doctor();
            break;
        case 2:
            add_staff();
            break;
        case 3:

            break;
        case 4:
            change_password();
            break;
        case 5:
            add_ambulance_services();
            break;
        case 6:
            book_ambulance();
            break;
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
        printf("Welcome Admin! You have access to administrative options.\n");
        admin();
    } else if (strcmp(mode, "Med staff") == 0) {
        printf("Welcome Medical Staff! You have access to medical options.\n");
        // Add medical options here
    } else if (strcmp(mode, "Support staff") == 0) {
        printf("Welcome Support Staff! You have access to support options.\n");
        // Add support options here
    } else {
        printf("Invalid mode.\n");
    }
}

int main() {
    printf("MEDFILES\n\nWelcome To MedFiles\n");
    printf("Choose mode: \n");
    printf("1. Admin\n");
    printf("2. Medical staff\n");
    printf("3. Support staff\n");

 int mode_choice;
    do {
        printf("Enter option: ");
        scanf("%d", &mode_choice);

        if (mode_choice < 1 || mode_choice > 3) {
            printf("Invalid mode choice. Please enter a number between 1 and 3.\n");
        }
    } while (mode_choice <1 || mode_choice>3);

    char mode[20];
    switch (mode_choice) {
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
            printf("Invalid mode choice.\n");
            return 1;
    }

    char user_id[MAX_ID_LENGTH];
    printf("Enter your user ID: ");
    scanf("%s", user_id);

    if (check_credentials(mode, user_id)) {
        display_options(mode);
    }
    else {
        printf("Invalid user ID or mode.\n");
    }

    return 0;
}
