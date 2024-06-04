#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_APPOINTMENTS 100

typedef struct Appointment {
    char patient_name[50];
    char doctor_name[50];
    char date[20];
    char time[10];
} Appointment;

char* create_appointment_filename(const char* username) {
    size_t filename_len = strlen(username) + strlen("_appointments.csv") + 1;
    char* filename = malloc(filename_len * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "Error allocating memory for filename.\n");
        return NULL;
    }
    snprintf(filename, filename_len, "%s_appointments.csv", username);
    //printf("Filename: %s\n", filename); // Print filename for debugging
    return filename;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_appointment(const char* username) {
    Appointment newAppointment;

    printf("Enter details:\n");
    printf("Enter patient name: ");
    fgets(newAppointment.patient_name, sizeof(newAppointment.patient_name), stdin);
    newAppointment.patient_name[strcspn(newAppointment.patient_name, "\n")] = '\0'; // Remove trailing newline
    printf("Enter date (DD/MM/YYYY): ");
    fgets(newAppointment.date, sizeof(newAppointment.date), stdin);
    newAppointment.date[strcspn(newAppointment.date, "\n")] = '\0'; // Remove trailing newline
    printf("Enter time (HH:MM AM/PM): ");
    fgets(newAppointment.time, sizeof(newAppointment.time), stdin);
    newAppointment.time[strcspn(newAppointment.time, "\n")] = '\0'; // Remove trailing newline

    char *filename = create_appointment_filename(username);
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        // Attempt to create the file
        file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            free(filename);
            return;
        }
    }

    int file_just_created = (ftell(file) == 0);
    if (file_just_created) {
        fprintf(file, "Patient Name,Date,Time\n");
    }
    fprintf(file, "%s,%s,%s\n", newAppointment.patient_name, newAppointment.date, newAppointment.time);

    fclose(file);
    free(filename);
    printf("Appointment added successfully.\n");
    printf("Press Enter to continue...");
    clear_input_buffer();
    getchar(); // Wait for Enter key
    // Clear screen after operation
    // clear_screen(); // Uncomment this line if you have the clear_screen() function
}
