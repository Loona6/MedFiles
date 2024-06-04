#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct {
    char name[50];
    char contact[12];
    char age[3];
    char gender[7];
    char date[11]; // Assuming date is stored as "YYYY-MM-DD"
} Patient;

Patient patient;

void add_patient() {
    // Get the current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(patient.date, sizeof(patient.date), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

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

    FILE *file = fopen("patient.csv", "r");
    int file_exists = (file != NULL);
    if (file != NULL) {
        fclose(file);
    }

    file = fopen("patient.csv", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write header if file didn't exist
    if (!file_exists) {
        fprintf(file, "Name,Age,Gender,Contact,Date\n");
    }

    // Write patient details to the file
    fprintf(file, "%s,%s,%s,%s,%s\n", patient.name, patient.age, patient.gender, patient.contact, patient.date);

    fclose(file);
    printf("Patient added successfully.\n");

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}
