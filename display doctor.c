#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LENGTH 20
#define FILENAME "doctors.csv"

struct Doctor {
    char first_name[50];
    char last_name[50];
    char user_id[MAX_ID_LENGTH];
};

void display_doctors() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Doctor doctor;
    int count = 0;

    while (fscanf(file, "%[^,],%[^,],%s\n", doctor.first_name, doctor.last_name, doctor.user_id) != EOF) {
        count++;
        printf("%d. %s %s (User ID: %s)\n", count, doctor.first_name, doctor.last_name, doctor.user_id);
    }

    fclose(file);

    if (count == 0) {
        printf("No doctors found.\n");
    }



}
