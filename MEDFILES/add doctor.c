#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>
#define MAX_ID_LENGTH 20
void add_doctor() {
    char name_1[500], name_2[500];
    char user_id[MAX_ID_LENGTH];

    printf("Enter doctor's name\nFirst name:");
    scanf("%s", name_1);
    printf("Last name:");
    scanf("%s", name_2);
    printf("Enter doctor's user ID: ");
    scanf("%s", user_id);

      // Open the CSV file in append mode
    FILE *file = fopen("doctors.csv", "a");
    if (file == NULL) {
        // If file doesn't exist, create a new file
        file = fopen("doctors.csv", "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }
        // Write header to the file
        fprintf(file, "First Name,Last Name,User ID\n");
    }

    // Write doctor's information to the file
    fprintf(file, "%s,%s,%s\n", name_1,name_2,user_id);

    // Close the file
    fclose(file);

    printf("Doctor %s %s added successfully with user ID %s.\n", name_1,name_2, user_id);

    system("cls");
}
