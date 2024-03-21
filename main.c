#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 500
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// Structures
struct Patient
{
    int id;
    char name[50];
    int age;
};

struct Doctor
{
    int id;
    char name[50];
    char specialization[50];
};

struct Appointment
{
    int appointment_id;
    int patient_id;
    int doctor_id;
    char date[15];
    float charges;
};

typedef struct
{
    int id;             // Ambulance ID
    char contact[20];   // Contact number
    bool isAvailable;   // Availability status
} Ambulance;

Ambulance ambulances[5] =
{
    {1, "123-456-7890", true},
    {2, "098-765-4321", true},
    {3, "555-123-4567", true},
    {4, "666-666-6666", true},
    {5, "777-888-9999", true}
};

// Function prototypes
void addPatient(struct Patient patients[], int *patient_count);
void addDoctor(struct Doctor doctors[], int *doctor_count);
void addAppointment(struct Appointment appointments[], int *appointment_count, struct Patient patients[], int patient_count, struct Doctor doctors[], int doctor_count);
void displayPatients(struct Patient patients[], int patient_count);
void displayDoctors(struct Doctor doctors[], int doctor_count);
void displayAppointments(struct Appointment appointments[], int appointment_count, struct Patient patients[], int patient_count, struct Doctor doctors[], int doctor_count);
char* getPatientName(struct Patient patients[], int patient_count, int patient_id);
char* getDoctorName(struct Doctor doctors[], int doctor_count, int doctor_id);
void showAvailableAmbulances(Ambulance ambulances[], int size);
void bookAmbulance(Ambulance ambulances[], int size, int ambulanceId);

int main()
{
    struct Patient patients[MAX_PATIENTS];
    struct Doctor doctors[MAX_DOCTORS];
    struct Appointment appointments[MAX_APPOINTMENTS];
    int patient_count = 0, doctor_count = 0, appointment_count = 0;
    int choice;

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char correct_username[] = "user";
    char correct_password[] = "password";

    printf("\t\t\t\t\t\tLOGIN to enter MEDFILES\n");

    // Prompt user for username
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from username if present
    username[strcspn(username, "\n")] = 0;

    // Prompt user for password
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from password if present
    password[strcspn(password, "\n")] = 0;

    // Check if the entered username and password match
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0)
    {
        system("cls");
        printf("\t\t\t\t\t\t Login successful!!\n");

        do
        {
            printf("\t\t\t\t\t\tWelcome to Medfiles\n\n\n");
            printf("\t\t\t1. Add Patient\n");
            printf("\t\t\t2. Add Doctor\n");
            printf("\t\t\t3. Add Appointment\n");
            printf("\t\t\t4. Display Patients\n");
            printf("\t\t\t5. Display Doctors\n");
            printf("\t\t\t6. Display Appointments\n");
            printf("\t\t\t7. Ambulance Service\n");
            printf("\t\t\t8. Exit\n");
            printf("\t\t\tEnter your choice: ");
            scanf("%d", &choice);
            system("cls");

            switch (choice)
            {
            case 1:
                addPatient(patients, &patient_count);
                break;
            case 2:
                addDoctor(doctors, &doctor_count);
                break;
            case 3:
                addAppointment(appointments, &appointment_count, patients, patient_count, doctors, doctor_count);
                break;
            case 4:
                displayPatients(patients, patient_count);
                break;
            case 5:
                displayDoctors(doctors, doctor_count);
                break;
            case 6:
                displayAppointments(appointments, appointment_count, patients, patient_count, doctors, doctor_count);
                break;
            case 7:
                showAvailableAmbulances(ambulances, 5);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
        while (choice != 8);
    }
    else
    {
        printf("Invalid username or password. Please try again.\n");
        getchar(); // Clear input buffer
        getchar(); // Wait for Enter key
        //system("cls");
    }

    return 0;
}

void addPatient(struct Patient patients[], int *patient_count)
{
    if (*patient_count < MAX_PATIENTS)
    {
        printf("\nEnter patient ID: ");
        scanf("%d", &patients[*patient_count].id);
        printf("Enter patient name: ");
        scanf("%s", patients[*patient_count].name);
        printf("Enter patient age: ");
        scanf("%d", &patients[*patient_count].age);
        (*patient_count)++;
        printf("Patient added successfully.\n");
    }
    else
    {
        printf("Maximum number of patients reached.\n");
    }
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}

void addDoctor(struct Doctor doctors[], int *doctor_count)
{
    if (*doctor_count < MAX_DOCTORS)
    {
        printf("\nEnter doctor ID: ");
        scanf("%d", &doctors[*doctor_count].id);
        printf("Enter doctor name: ");
        scanf("%s", doctors[*doctor_count].name);
        printf("Enter doctor's specialization: ");
        scanf("%s", doctors[*doctor_count].specialization);
        (*doctor_count)++;
        printf("Doctor added successfully.\n");
    }
    else
    {
        printf("Maximum number of doctors reached.\n");
    }
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}

void addAppointment(struct Appointment appointments[], int *appointment_count, struct Patient patients[], int patient_count, struct Doctor doctors[], int doctor_count)
{
    if (*appointment_count < MAX_APPOINTMENTS)
    {
        printf("\nEnter appointment ID: ");
        scanf("%d", &appointments[*appointment_count].appointment_id);
        printf("Enter patient ID: ");
        scanf("%d", &appointments[*appointment_count].patient_id);
        printf("Enter doctor ID: ");
        scanf("%d", &appointments[*appointment_count].doctor_id);
        printf("Enter appointment date (DD/MM/YYYY): ");
        scanf("%s", appointments[*appointment_count].date);
        printf("Enter charges for appointment: ");
        scanf("%f", &appointments[*appointment_count].charges);
        (*appointment_count)++;
        printf("Appointment added successfully.\n");
    }
    else
    {
        printf("Maximum number of appointments reached.\n");
    }
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}

void displayPatients(struct Patient patients[], int patient_count)
{
    if (patient_count > 0)
    {
        printf("\nPatient Details:\n");
        printf("ID\tName\tAge\n");
        for (int i = 0; i < patient_count; i++)
        {
            printf("%d\t%s\t%d\n", patients[i].id, patients[i].name, patients[i].age);
        }
    }
    else
    {
        printf("No patients to display.\n");
    }
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}

void displayDoctors(struct Doctor doctors[], int doctor_count)
{
    if (doctor_count > 0)
    {
        printf("\nDoctor Details:\n");
        printf("ID\tName\tSpecialization\n");
        for (int i = 0; i < doctor_count; i++)
        {
            printf("%d\t%s\t%s\n", doctors[i].id, doctors[i].name, doctors[i].specialization);
        }
    }
    else
    {
        printf("No doctors to display.\n");
    }
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}

void displayAppointments(struct Appointment appointments[], int appointment_count, struct Patient patients[], int patient_count, struct Doctor doctors[], int doctor_count)
{
    if (appointment_count > 0)
    {
        printf("\nAppointment Details:\n");
        printf("ID\tPatient\tDoctor\tDate\tCharges\n");
        for (int i = 0; i < appointment_count; i++)
        {
            printf("%d\t%s\t%s\t%s\t%.2f\n", appointments[i].appointment_id, getPatientName(patients, patient_count, appointments[i].patient_id), getDoctorName(doctors, doctor_count, appointments[i].doctor_id), appointments[i].date, appointments[i].charges);
        }
    }
    else
    {
        printf("No appointments to display.\n");
    }
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}

char* getPatientName(struct Patient patients[], int patient_count, int patient_id)
{
    for (int i = 0; i < patient_count; i++)
    {
        if (patients[i].id == patient_id)
        {
            return patients[i].name;
        }
    }
    return "Unknown";
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}

char* getDoctorName(struct Doctor doctors[], int doctor_count, int doctor_id)
{
    for (int i = 0; i < doctor_count; i++)
    {
        if (doctors[i].id == doctor_id)
        {
            return doctors[i].name;
        }
    }
    return "Unknown";
    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");



}
void showAvailableAmbulances(Ambulance ambulances[], int size)
{
    printf("ID\tContact Number\n");
    for (int i = 0; i < size; i++)
    {
        if (ambulances[i].isAvailable)
        {
            printf("%d\t%s\n", ambulances[i].id, ambulances[i].contact);
        }
    }

    printf("Press Enter to return to the main page...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key
    system("cls");
}
