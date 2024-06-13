#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>
#define MAX_ID_LENGTH 20
#define FILENAME "doctors.csv"
void add_doctor() {
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
    if (file == NULL) {
        file = fopen(FILENAME, "w");
        if (file == NULL) {
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
