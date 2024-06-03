#include<stdio.h>
#include<string.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_CABINS 10

// Structure to represent a cabin
struct Cabin {
    int cabinNumber;
    bool isBooked;
    int patientID; // Assuming each patient has a unique ID
};

// Initialize cabins
void initializeCabins(struct Cabin cabins[], int numCabins) {
    for (int i = 0; i < numCabins; i++) {
        cabins[i].cabinNumber = i + 1;
        cabins[i].isBooked = false;
        cabins[i].patientID = -1; // No patient initially
    }
}

// Display available cabins
void displayAvailableCabins(struct Cabin cabins[], int numCabins) {
    printf("\nAvailable Cabins:\n");
    for (int i = 0; i < numCabins; i++) {
        if (!cabins[i].isBooked) {
            printf("Cabin %d\n", cabins[i].cabinNumber);
        }
    }
}

// Book a cabin
void bookCabin(struct Cabin cabins[], int numCabins) {
    int cabinChoice;
    printf("\nEnter the cabin number you want to book: ");
    scanf("%d", &cabinChoice);

    if (cabinChoice < 1 || cabinChoice > numCabins) {
        printf("Invalid cabin number.\n");
        return;
    }

    if (cabins[cabinChoice - 1].isBooked) {
        printf("Cabin %d is already booked.\n", cabinChoice);
    } else {
        cabins[cabinChoice - 1].isBooked = true;
        printf("Cabin %d booked successfully.\n", cabinChoice);
        // Here you can prompt for patient ID and store it if necessary
    }
}

// Cancel booking
void cancelBooking(struct Cabin cabins[], int numCabins) {
    int cabinChoice;
    printf("\nEnter the cabin number you want to cancel booking for: ");
    scanf("%d", &cabinChoice);

    if (cabinChoice < 1 || cabinChoice > numCabins) {
        printf("Invalid cabin number.\n");
        return;
    }

    if (!cabins[cabinChoice - 1].isBooked) {
        printf("Cabin %d is not booked.\n", cabinChoice);
    } else {
        cabins[cabinChoice - 1].isBooked = false;
        printf("Booking for cabin %d canceled successfully.\n", cabinChoice);
        // Optionally, you can clear the patient ID here
    }
}

int chose() {
    struct Cabin cabins[NUM_CABINS];
    int choice;
    initializeCabins(cabins, NUM_CABINS);

    do {
        printf("\n\t\t1.View Available Cabins\n");
        printf("\n\t\t2.Book a Cabin\n");
        printf("\n\t\t3.Cancel Booking\n");
        printf("\n\t\t4.Exit\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableCabins(cabins, NUM_CABINS);
                break;
            case 2:
                bookCabin(cabins, NUM_CABINS);
                break;
            case 3:
                cancelBooking(cabins, NUM_CABINS);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }while (choice != 4);
}
