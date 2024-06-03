#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME2 "doctors.csv"
#define MAX_ID_LENGTH 20
#define FILENAME3 "staff.csv"
#define MAX_CONTACT_LENGTH 15
#define MAX_AMBULANCES 1
#define TEMP_FILENAME "temp.csv"
#define MAX_LINE_LENGTH 256
#define FILENAME "ambulance_services.csv"

void clear_screen() {
    // Platform-specific screen clearing
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

struct Ambulance {
    char number[50];
    char contact[MAX_CONTACT_LENGTH];
};

struct Ambulance ambulances[MAX_AMBULANCES];

void add_doctor() {
    char first_name[500];
    char last_name[500];
    char user_id[MAX_ID_LENGTH];

    printf("Enter doctor's first name: ");
    scanf("%s", first_name);
    printf("Enter doctor's last name: ");
    scanf("%s", last_name);
    printf("Enter doctor's user ID: ");
    scanf("%s", user_id);

    FILE *file = fopen(FILENAME2, "a");
    if (file == NULL) {
        file = fopen(FILENAME2, "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }

        fprintf(file, "First Name,Last Name,User ID\n");
    }

    fprintf(file, "%s,%s,%s\n", first_name, last_name, user_id);
    fclose(file);

    printf("Doctor %s %s added successfully with user ID %s.\n", first_name, last_name, user_id);

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}

void add_staff() {
    char first_name[500];
    char last_name[500];
    char user_id[MAX_ID_LENGTH];

    printf("Enter staff's first name: ");
    scanf("%s", first_name);
    printf("Enter staff's last name: ");
    scanf("%s", last_name);
    printf("Enter staff's user ID: ");
    scanf("%s", user_id);

    FILE *file = fopen(FILENAME3, "a");
    if (file == NULL) {
        file = fopen(FILENAME3, "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }

        fprintf(file, "First Name,Last Name,User ID\n");
    }

    fprintf(file, "%s,%s,%s\n", first_name, last_name, user_id);
    fclose(file);

    printf("Staff member %s %s added successfully with user ID %s.\n", first_name, last_name, user_id);

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}

void add_ambulance() {
    printf("Enter ambulance details:\n");
    for (int i = 0; i < MAX_AMBULANCES; i++) {
        printf("Enter ambulance number for Ambulance %d: ", i + 1);
        scanf("%s", ambulances[i].number);
        printf("Enter contact number for Ambulance %d: ", i + 1);
        scanf("%s", ambulances[i].contact);
    }

    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }

    for (int i = 0; i < MAX_AMBULANCES; i++) {
        fprintf(file, "%s,%s\n", ambulances[i].number, ambulances[i].contact);
    }

    fclose(file);
    printf("Ambulance services added successfully.\n");

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}

void delete_ambulance() {
    char ambulance_id[20];
    char line[MAX_LINE_LENGTH];
    int found = 0;

    printf("Enter the ambulance ID to delete: ");
    scanf("%s", ambulance_id);

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *temp_file = fopen(TEMP_FILENAME, "w");
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    // Copy the header
    if (fgets(line, sizeof(line), file) != NULL) {
        fputs(line, temp_file);
    }

    // Copy the lines except the one to delete
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, ambulance_id) != NULL) {
            found = 1;
            continue;
        }
        fputs(line, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(FILENAME);
        rename(TEMP_FILENAME, FILENAME);
        printf("Ambulance with ID %s deleted successfully.\n", ambulance_id);
    } else {
        remove(TEMP_FILENAME);
        printf("Ambulance with ID %s not found.\n", ambulance_id);
    }

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}

void display_doctors() {
    FILE *file = fopen(FILENAME2, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Doctor {
        char first_name[500];
        char last_name[500];
        char user_id[MAX_ID_LENGTH];
    } doctor;

    int count = 0;

    // Skip header line
    char header[1000];
    if (fgets(header, sizeof(header), file) == NULL) {
        printf("Error reading file header.\n");
        fclose(file);
        return;
    }

    printf("Doctors:\n");
    printf("%-20s%-20s%s\n", "First Name", "Last Name", "User ID");
    printf("-------------------------------------------------------------\n");

    while (fscanf(file, "%[^,],%[^,],%s\n", doctor.first_name, doctor.last_name, doctor.user_id) != EOF) {
        count++;
        printf("%-20s%-20s%s\n", doctor.first_name, doctor.last_name, doctor.user_id);
    }

    fclose(file);

    if (count == 0) {
        printf("No doctors found.\n");
    }

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}

void display_staff() {
    FILE *file = fopen(FILENAME3, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Staff {
        char first_name[500];
        char last_name[500];
        char user_id[MAX_ID_LENGTH];
    } staff;

    int count = 0;

    // Skip header line
    char header[1000];
    if (fgets(header, sizeof(header), file) == NULL) {
        printf("Error reading file header.\n");
        fclose(file);
        return;
    }

    printf("Staff Members:\n");
    printf("%-20s%-20s%s\n", "First Name", "Last Name", "User ID");
    printf("-------------------------------------------------------------\n");

    while (fscanf(file, "%[^,],%[^,],%s\n", staff.first_name, staff.last_name, staff.user_id) != EOF) {
        count++;
        printf("%-20s%-20s%s\n", staff.first_name, staff.last_name, staff.user_id);
    }

    fclose(file);

    if (count == 0) {
        printf("No staff members found.\n");
    }

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}

void display_ambulance() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Ambulance ambulance;
    int count = 0;

    // Skip header line if present
    char header[1000];
    if (fgets(header, sizeof(header), file) != NULL && strchr(header, ',') == NULL) {
        rewind(file);  // Reset file pointer if no header
    }

    printf("Ambulance Services:\n");
    printf("%-20s%-20s\n", "ID", "Contact");
    printf("-------------------------------------------------------------\n");

    while (fscanf(file, "%[^,],%s\n", ambulance.number, ambulance.contact) != EOF) {
        count++;
        printf("%-20s%-20s\n", ambulance.number, ambulance.contact);
    }

    fclose(file);

    if (count == 0) {
        printf("No ambulance services found.\n");
    }

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}