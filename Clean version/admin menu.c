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
    char status[10];
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
  printf("Enter doctor's password: ");
  char pass[100];
  scanf("%s", pass);

  FILE *f = fopen("Medical_credentials.txt", "a");
  if (f == NULL) {
    f = fopen("Medical_credentials.txt", "w");
    if (f == NULL) {
      printf("Error creating file.\n");
      return;
    }
  }
  fprintf(f, "%s,%s\n", user_id, pass);
  fclose(f);

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
    printf("Enter staff's password: ");
    char pass[100];
    scanf("%s", pass);

      FILE *f = fopen("Support_credentials.txt", "a");
      if (f == NULL) {
        f = fopen("Support_credentials.txt", "w");
        if (f == NULL) {
          printf("Error creating file.\n");
          return;
        }
      }
      fprintf(f, "%s,%s\n", user_id, pass);
      fclose(f);

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
        strcpy(ambulances[i].status, "Unbooked"); // Set status to unbooked
    }

    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }

    for (int i = 0; i < MAX_AMBULANCES; i++) {
        fprintf(file, "%s,%s,%s\n", ambulances[i].number, ambulances[i].contact, ambulances[i].status);
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
    scanf("%19s", ambulance_id); // Limit input length to prevent buffer overflow

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    FILE *temp_file = fopen(TEMP_FILENAME, "w");
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    // Copy the first row
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error: file is empty.\n");
        fclose(file);
        fclose(temp_file);
        remove(TEMP_FILENAME); // Clean up temporary file
        return;
    }
    fputs(line, temp_file);

    // Copy the lines except the one to delete
    while (fgets(line, sizeof(line), file) != NULL) {
        char temp_line[MAX_LINE_LENGTH];
        strcpy(temp_line, line);
        char *id = strtok(temp_line, ",");
        if (id != NULL && strcmp(id, ambulance_id) == 0) {
            found = 1;
            continue; // Skip this line
        }
        fputs(line, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        if (remove(FILENAME) != 0) {
            printf("Error deleting original file.\n");
            return;
        }
        if (rename(TEMP_FILENAME, FILENAME) != 0) {
            printf("Error renaming temporary file.\n");
            return;
        }
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
    printf("%-20s%-20s%-20s\n", "ID", "Contact", "Status");
    printf("-------------------------------------------------------------\n");
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token;
        token = strtok(line, ",");
        if (token != NULL) strcpy(ambulance.number, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(ambulance.contact, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(ambulance.status, token);
        count++;
        printf("%-20s%-20s%-20s\n", ambulance.number, ambulance.contact,ambulance.status);
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
