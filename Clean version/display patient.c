#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PATIENTS 100

typedef struct {
    char name[50];
    char contact[12];
    char age[3];
    char gender[7];
    char date[11]; // Assuming date is stored as "YYYY-MM-DD"
} Patient;

// Function to compare two patients by name for qsort (case-insensitive)
int compare_patients_by_name(const void *a, const void *b) {
    Patient *patientA = (Patient *)a;
    Patient *patientB = (Patient *)b;
    return strcasecmp(patientA->name, patientB->name);
}



void display_patients(int sort_by) {
    FILE *file = fopen("patient.csv", "r");
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
