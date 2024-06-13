#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

#define MAX_ID_LENGTH 20
#define FILENAME3 "doctors.csv"
#define MAX_APPOINTMENTS 100
#define FILENAME2 "appointments.csv"

typedef struct
{
    char name[50];
    char contact[12];
    char age[3];
    char gender[7];
} Patient;

Patient patient;

struct Doctor
{
    char first_name[50];
    char last_name[50];
    char user_id[MAX_ID_LENGTH];
};

typedef struct Appointment
{
    char patient_name[50];
    char doctor_name[50];
    char date[20];
    char time[10];
} Appointment;

Appointment newAppointment;

void display_patients()
{
    FILE *file = fopen("patient.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }


    char line[100];
    fgets(line, sizeof(line), file);


    while (fgets(line, sizeof(line), file))
    {

        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]\n", patient.name, patient.age, patient.gender, patient.contact);


        printf("Name: %s\n", patient.name);
        printf("Age: %s\n", patient.age);
        printf("Gender: %s\n", patient.gender);
        printf("Contact: %s\n", patient.contact);
        printf("\n");
    }

    fclose(file);
}






void display_doctors()
{
    FILE *file = fopen(FILENAME3, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Doctor doctor;
    int count = 0;

    while (fscanf(file, "%[^,],%[^,],%s\n", doctor.first_name, doctor.last_name, doctor.user_id) != EOF)
    {
        count++;
        printf("%d. %s %s (User ID: %s)\n", count, doctor.first_name, doctor.last_name, doctor.user_id);
    }

    fclose(file);

    if (count == 0)
    {
        printf("No doctors found.\n");
    }



}




// Function to display appointments from the file
void display_appointments()
{
    FILE *file = fopen(FILENAME2, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Read the header line
    char line[100];
    fgets(line, sizeof(line), file);

    int count = 0;
    while (fgets(line, sizeof(line), file) && count < MAX_APPOINTMENTS)
    {
        // Parse the line into the appointment fields
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^\n]\n", newAppointment.patient_name, newAppointment.doctor_name, newAppointment.date, newAppointment.time) == 4)
        {
            count++;
            // Print the appointment data in markdown table format
            printf("| %-15s | %-15s | %-10s | %-8s |\n", newAppointment.patient_name, newAppointment.doctor_name, newAppointment.date, newAppointment.time);
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("No appointments found.\n");
    }
}
