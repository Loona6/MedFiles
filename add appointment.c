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
} Appointment;

Appointment newAppointment;

void add_appointment() {
            printf("Enter details:\n");
            printf("Enter patient name: ");
            scanf("%s", newAppointment.patient_name);
            printf("\n");
            printf("Enter doctor's name: ");
            scanf("%s", newAppointment.doctor_name);
            printf("\n");
            printf("Enter date(DD/MM/YYYY): ");
            scanf("%s", newAppointment.date);
            printf("\n");
            printf("Enter time(HH:MMAM/PM): ");
            scanf("%s", newAppointment.time);
            printf("\n");

        FILE *file = fopen(FILENAME, "a");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }

        fprintf(file, "%s,%s,%s,%s\n\n\n", newAppointment.patient_name, newAppointment.doctor_name, newAppointment.date, newAppointment.time);

        fclose(file);
        printf("Appointment added successfully.\n");

}
