#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

typedef struct {
    char name[50];
    char contact[12];
    char age[3];
    char gender[7];
} Patient;

Patient patient;

void display_patients() {
    FILE *file = fopen("patient.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read the header line
    char line[100];
    fgets(line, sizeof(line), file);

    // Read the patient data lines
    while (fgets(line, sizeof(line), file)) {
        // Parse the line into the patient fields
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]\n", patient.name, patient.age, patient.gender, patient.contact);

        // Print the patient data
        printf("Name: %s\n", patient.name);
        printf("Age: %s\n", patient.age);
        printf("Gender: %s\n", patient.gender);
        printf("Contact: %s\n", patient.contact);
        printf("\n");
    }

    fclose(file);
}
