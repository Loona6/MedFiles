#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#define FILENAME1 "patient.csv"
#define MAX_ID_LENGTH 20
#define FILENAME2 "doctors.csv"
#define MAX_APPOINTMENTS 100
#define FILENAME3 "appointments.csv"
#define MAX_AMBULANCES 1
#define MAX_ID_LENGTH 20

typedef struct
{
    char name[50];
    char contact[12];
    char age[3];
    char gender[7];
} Patient;

Patient patient;

typedef struct
{
    char number[MAX_ID_LENGTH];
    char contact[MAX_ID_LENGTH];
    char status[20]; // "Booked" or "Unbooked"
    char booked_by[MAX_ID_LENGTH];
} Ambulance;

Ambulance ambulances[MAX_AMBULANCES];

typedef struct Appointment
{
    char patient_name[50];
    char doctor_name[50];
    char date[20];
    char time[10];
} Appointment;

Appointment newAppointment;


void add_patient()
{
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

    FILE *file = fopen(FILENAME1, "a");
    if (file == NULL)
    {
        printf("Error creating file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s\n", patient.name, patient.age, patient.gender, patient.contact);

    fclose(file);
    printf("Patient added successfully.\n");

}


void add_doctor()
{
    char name_1[500];
    char name_2[500];
    char user_id[MAX_ID_LENGTH];

    printf("Enter doctor's name\nFirst name:");
    scanf("%s", name_1);
    printf("Last name:");
    scanf("%s", name_2);
    printf("Enter doctor's user ID: ");
    scanf("%s", user_id);


    FILE *file = fopen("doctors.csv", "a");
    if (file == NULL)
    {
        file = fopen(FILENAME2, "w");
        if (file == NULL)
        {
            printf("Error creating file.\n");
            return;
        }

        fprintf(file, "First Name,Last Name,User ID\n");
    }


    fprintf(file, "%s,%s,%s\n", name_1,name_2,user_id);


    fclose(file);

    printf("Doctor %s %s added successfully with user ID %s.\n", name_1,name_2, user_id);

    //system("cls");
}



void add_appointment()
{
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

    FILE *file = fopen(FILENAME3, "a");
    if (file == NULL)
    {
        printf("Error creating file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s\n\n\n", newAppointment.patient_name, newAppointment.doctor_name, newAppointment.date, newAppointment.time);

    fclose(file);
    printf("Appointment added successfully.\n");

}




void add_ambulance()
{
    printf("Enter ambulance details:\n");
    for (int i = 0; i < MAX_AMBULANCES; i++)
    {
        printf("Enter ambulance number for Ambulance %d: ", i + 1);
        scanf("%s", ambulances[i].number);
        printf("Enter contact number for Ambulance %d: ", i + 1);
        scanf("%s", ambulances[i].contact);
        strcpy(ambulances[i].status, "Unbooked");
        strcpy(ambulances[i].booked_by, "");
    }

    FILE *file = fopen("ambulance_services.csv", "a");
    if (file == NULL)
    {
        printf("Error creating file.\n");
        return;
    }

    // Write ambulance details to the file
    //fprintf(file, "Number,Contact,Status,Booked By\n");
    for (int i = 0; i < MAX_AMBULANCES; i++)
    {
        fprintf(file, "%s,%s,%s,%s\n", ambulances[i].number, ambulances[i].contact, ambulances[i].status, ambulances[i].booked_by);
    }

    fclose(file);
    printf("Ambulance services added successfully.\n");

}


