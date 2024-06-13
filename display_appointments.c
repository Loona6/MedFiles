#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_APPOINTMENTS 100
#define FILENAME "appointments.csv"

typedef struct Appointment {
    char patient_name[50];
    char doctor_name[50];
    char date[20];
    char time[10];
} Appointment;

Appointment newAppointment;

// Function to display appointments from the file
void display_appointments() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read the header line
    char line[100];
    fgets(line, sizeof(line), file);

    int count = 0;
    while (fgets(line, sizeof(line), file) && count < MAX_APPOINTMENTS) {
        // Parse the line into the appointment fields
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^\n]\n", newAppointment.patient_name, newAppointment.doctor_name, newAppointment.date, newAppointment.time) == 4) {
            count++;
            // Print the appointment data in markdown table format
            printf("| %-15s | %-15s | %-10s | %-8s |\n", newAppointment.patient_name, newAppointment.doctor_name, newAppointment.date, newAppointment.time);
        }
    }

    fclose(file);

    if (count == 0) {
        printf("No appointments found.\n");
    }
}
