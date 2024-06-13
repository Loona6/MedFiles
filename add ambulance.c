#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#define MAX_AMBULANCES 1
#define MAX_ID_LENGTH 20
typedef struct {
    char number[MAX_ID_LENGTH];
    char contact[MAX_ID_LENGTH];
    char status[20]; // "Booked" or "Unbooked"
    char booked_by[MAX_ID_LENGTH];
} Ambulance;

Ambulance ambulances[MAX_AMBULANCES];

void add_ambulance() {
        printf("Enter ambulance details:\n");
        for (int i = 0; i < MAX_AMBULANCES; i++) {
            printf("Enter ambulance number for Ambulance %d: ", i + 1);
            scanf("%s", ambulances[i].number);
            printf("Enter contact number for Ambulance %d: ", i + 1);
            scanf("%s", ambulances[i].contact);
            strcpy(ambulances[i].status, "Unbooked");
            strcpy(ambulances[i].booked_by, "");
        }

        FILE *file = fopen("ambulance_services.csv", "a");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }

        // Write ambulance details to the file
        //fprintf(file, "Number,Contact,Status,Booked By\n");
        for (int i = 0; i < MAX_AMBULANCES; i++) {
            fprintf(file, "%s,%s,%s,%s\n", ambulances[i].number, ambulances[i].contact, ambulances[i].status, ambulances[i].booked_by);
        }

        fclose(file);
        printf("Ambulance services added successfully.\n");

}
