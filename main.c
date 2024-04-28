#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

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


int main()
{
    login();

    Main_menu();
}
