#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TESTS 5
#define MAX_PRICE 5
#define MAX_NAME_LENGTH 50

// Structure to represent a lab test
struct LabTest {
    int testID;
    char testName[MAX_NAME_LENGTH];
    //int testprice[MAX_PRICE];
    bool testisBooked;
    //int patientID; // Assuming each patient has a unique ID
};

// Initialize lab tests
void initializeLabTests(struct LabTest tests[], int numTests) {
    // Let's assume some initial test names
    char* testNames[] = {"Blood Test\t\t\t100tk", "Urine Test\t\t\t200tk", "X-Ray\t\t\t400tk", "MRI\t\t\t\t2000tk", "CT Scan\t\t\t3000tk"};
    //int* testPrices[]= {"100", "200","300"};
    for (int i = 0; i < numTests; i++) {
        tests[i].testID = i + 1;
        strcpy(tests[i].testName, testNames[i % 5]);
        tests[i].testisBooked = false;
        //tests[i].patientID = -1; // No patient initially
    }
}

// Display available lab tests
void displayAvailableTests(struct LabTest tests[], int numTests) {
    printf("\n\tAvailable Lab Tests:\t\tPrice:\n");
    for (int i = 0; i < numTests; i++) {
        if (!tests[i].testisBooked) {
            printf("\n%10d. %s\n", tests[i].testID, tests[i].testName);
        }
    }
}

// Book a lab test
void bookTest(struct LabTest tests[], int numTests) {
    int testChoice;
    printf("\n\tEnter the test ID you want to book: ");
    scanf("%d", &testChoice);

    if (testChoice < 1 || testChoice > numTests) {
        printf("Invalid test ID.\n");
        return;
    }

    if (tests[testChoice - 1].testisBooked) {
        printf("%s test is already booked.\n", tests[testChoice - 1].testName);
    } else {
        tests[testChoice - 1].testisBooked = true;
        printf("\nTest booked successfully.\n");
        // Here you can prompt for patient ID and store it if necessary
    }
}

// Cancel booking
void canceltestBooking(struct LabTest tests[], int numTests) {
    int testChoice;
    printf("\n\tEnter the test ID you want to cancel booking for: ");
    scanf("%d", &testChoice);

    if (testChoice < 1 || testChoice > numTests) {
        printf("Invalid test ID.\n");
        return;
    }

    if (!tests[testChoice - 1].testisBooked) {
        printf("\n%s Test is not booked.\n", tests[testChoice - 1].testName);
    } else {
        tests[testChoice - 1].testisBooked = false;
        printf("Booking for the test is canceled successfully.\n");
        // Optionally, you can clear the patient ID here
    }
}

int test() {
    struct LabTest tests[MAX_TESTS];
    int choice;

    // Initialize lab tests
    initializeLabTests(tests, MAX_TESTS);

    // Main menu
    do {
        printf("\n\n\t\t1.View Available Lab Tests\n");
        printf("\n\t\t2.Book a Lab Test\n");
        printf("\n\t\t3.Cancel Booking\n");
        printf("\n\t\t4.Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                displayAvailableTests(tests, MAX_TESTS);
                break;
            case 2:
                displayAvailableTests(tests, MAX_TESTS);
                bookTest(tests, MAX_TESTS);
                break;
            case 3:
                canceltestBooking(tests, MAX_TESTS);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);
}

