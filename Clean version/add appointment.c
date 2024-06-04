#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#define MAX_APPOINTMENTS 100
#define FILENAME "appointments.csv"
typedef struct Appointment {
    char patient_name[50];
    char doctor_name[50];
    char date[20];
    char time[10];
}Appointment;

Appointment newAppointment;

void add_appointment() {
    printf("Enter details:\n");
    printf("Enter patient name: ");
    scanf("%s", newAppointment.patient_name);
    printf("Enter doctor's name: ");
    scanf("%s", newAppointment.doctor_name);
    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", newAppointment.date);
    printf("Enter time (HH:MM AM/PM): ");
    scanf("%s", newAppointment.time);

    // Check if the file already exists
    FILE *file = fopen(FILENAME, "r");
    int file_exists = (file != NULL);
    if (file) {
        fclose(file);
    }

    // Open the file for appending
    file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write the header if the file was just created
    if (!file_exists) {
        fprintf(file, "Patient Name,Doctor Name,Date,Time\n");
    }

    // Write appointment details to the file
    fprintf(file, "%s,%s,%s,%s\n", newAppointment.patient_name, newAppointment.doctor_name, newAppointment.date, newAppointment.time);

    fclose(file);
    printf("Appointment added successfully.\n");

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    clear_screen(); // Clear screen after operation
}
