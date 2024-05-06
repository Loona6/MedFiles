#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

typedef struct {
    char name[50];
    char contact[12];
    char age[3]; // "Booked" or "Unbooked"
    char gender[7];
} Patient;

Patient patient;

void add_patient() {
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

        FILE *file = fopen("patient.csv", "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }

        // Write patient details to the file
        fprintf(file, "Name,Age,Gender,Contact\n");
            fprintf(file, "%s,%s,%s,%s\n", patient.name, patient.age, patient.gender, patient.contact);

        fclose(file);
        printf("Patient added successfully.\n");

}
int main(){

add_patient();

}
