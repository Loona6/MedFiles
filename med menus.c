
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define MAX_PATIENTS 100
typedef struct {
    char name[50];
    char contact[12];
    char age[3];
    char gender[7];
    char date[11]; // Assuming date is stored as "YYYY-MM-DD"
} Patient;

Patient patient;

char* create_patient_filename(const char* base_name) {
  // Allocate memory for the filename (including null terminator)
  size_t filename_len = strlen(base_name) + strlen("_patient.csv") + 1;
  char* filename = malloc(filename_len * sizeof(char));
  if (filename == NULL) {
    fprintf(stderr, "Error allocating memory for filename.\n");
    return NULL;
  }

  // Safely construct the filename using snprintf
  snprintf(filename, filename_len, "%s_patient.csv", base_name);

  return filename;
}

void add_patient() {
    // Get the current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(patient.date, sizeof(patient.date), "%04d/%02d/%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    // Prompt the user to enter patient details
    printf("Enter patient details:\n");
    printf("Enter patient name: ");
    scanf("%s", patient.name);
    printf("\n");
    printf("Enter patient age: ");
    scanf("%s", patient.age);
    printf("\n");
    printf("Enter patient gender: ");
    scanf("%s", patient.gender);
    printf("\n");
    printf("Enter patient contact: ");
    scanf("%s", patient.contact);
    printf("\n");

    // Create the filename
    char *filename = create_patient_filename(namesender());
    if (filename == NULL) {
        return;
    }

    // Check if the file exists
    FILE *file = fopen(filename, "r");
    int file_exists = (file != NULL);
    if (file) {
        fclose(file);
    }

    // Open the file for appending
    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        free(filename);
        return;
    }

    // Write the header if the file was just created
    if (!file_exists) {
        fprintf(file, "Name,Age,Gender,Contact,Date\n");
    }

    // Write the patient details to the file
    fprintf(file, "%s,%s,%s,%s,%s\n", patient.name, patient.age, patient.gender, patient.contact, patient.date);

    fclose(file);
    free(filename);
    printf("Patient added successfully.\n");

    // Prompt to press Enter before clearing the screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}


// Function to compare two patients by name for qsort (case-insensitive)
int compare_patients_by_name(const void *a, const void *b) {
    Patient *patientA = (Patient *)a;
    Patient *patientB = (Patient *)b;
    return strcasecmp(patientA->name, patientB->name);
}



void display_patients(int sort_by) {
    FILE *file = fopen(create_patient_filename(namesender()), "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Patient patients[MAX_PATIENTS];
    int count = 0;

    // Read the header line
    char line[1024];
    if (fgets(line, sizeof(line), file) == NULL || strchr(line, ',') == NULL) {
        printf("No patient data found.\n");
        fclose(file);
        return;
    }

    // Read the patient data lines
    while (fgets(line, sizeof(line), file) && count < MAX_PATIENTS) {
        // Parse the line into the patient fields
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", patients[count].name, patients[count].age, patients[count].gender, patients[count].contact, patients[count].date);
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("No patient data found.\n");
        return;
    }

    // Sort the patients based on the selected criterion
    if (sort_by == 1) {
        qsort(patients, count, sizeof(Patient), compare_patients_by_name);
    }
    else if (sort_by == 2) {
    printf("Patient Records:\n");
    printf("%-50s%-12s%-20s%-30s%-12s\n", "Name", "Age", "Gender", "Contact", "Date");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");

    // Print the sorted patient data
    for (int i = 0; i < count; i++) {
        printf("%-50s%-12s%-20s%-30s%-12s\n", patients[i].name, patients[i].age, patients[i].gender, patients[i].contact, patients[i].date);
    }

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
    }

    printf("Patient Records:\n");
    printf("%-50s%-12s%-20s%-30s%-12s\n", "Name", "Age", "Gender", "Contact", "Date");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");

    // Print the sorted patient data
    for (int i = 0; i < count; i++) {
        printf("%-50s%-12s%-20s%-30s%-12s\n", patients[i].name, patients[i].age, patients[i].gender, patients[i].contact, patients[i].date);
    }

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}

void search_patient() {
    char search_contact[12];
    printf("Enter patient contact to search: ");
    scanf("%s", search_contact);

    FILE *file = fopen(create_patient_filename(namesender()), "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Patient patients[MAX_PATIENTS];
    int count = 0;

    // Read the header line
    char line[1024];
    if (fgets(line, sizeof(line), file) == NULL || strchr(line, ',') == NULL) {
        printf("No patient data found.\n");
        fclose(file);
        return;
    }

    // Read the patient data lines
    while (fgets(line, sizeof(line), file) && count < MAX_PATIENTS) {
        // Parse the line into the patient fields
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", patients[count].name, patients[count].age, patients[count].gender, patients[count].contact, patients[count].date);
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("No patient data found.\n");
        return;
    }

    // Search for the patient by contact
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(patients[i].contact, search_contact) == 0) {
            printf("Patient Record Found:\n");
            printf("%-50s%-12s%-20s%-30s%-12s\n", "Name", "Age", "Gender", "Contact", "Date");
            printf("-----------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-50s%-12s%-20s%-30s%-12s\n", patients[i].name, patients[i].age, patients[i].gender, patients[i].contact, patients[i].date);
            found = 1;

            // Ask the user if they want to view patient details
            char choice[10];
            printf("Do you want to view patient details? (yes/no): ");
            scanf("%s", choice);

            if (strcasecmp(choice, "yes") == 0) {
                // Open the PDF file associated with the patient
                char pdf_filename[100];
                snprintf(pdf_filename, sizeof(pdf_filename), "%s.pdf", patients[i].name);
                char command[150];
                snprintf(command, sizeof(command), "xdg-open %s", pdf_filename);
                system(command);
            }

            // Prompt to press Enter before clearing the screen
            printf("Press Enter to continue...");
            getchar(); // Clear input buffer
            getchar(); // Wait for Enter key

            clear_screen(); // Clear screen after operation

            break; // Exit the loop after processing the patient
        }
    }

    if (!found) {
        printf("Patient not found.\n");
         // Prompt to press Enter before clearing the screen
            printf("Press Enter to continue...");
            getchar(); // Clear input buffer
            getchar(); // Wait for Enter key

            clear_screen(); // Clear screen after operation

    }

}



