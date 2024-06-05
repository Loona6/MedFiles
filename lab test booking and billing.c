#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TESTS 5
#define MAX_NAME_LENGTH 50

// Structure to represent a lab test
struct LabTest {
    int testID;
    char testName[MAX_NAME_LENGTH];
    bool testisBooked;
};

// Initialize lab tests
void initializeLabTests(struct LabTest tests[], int numTests) {
    char* testNames[] = {"Blood Test\t\t500 tk", "X-ray\t\t1000 tk", "MRI\t\t\t3000 tk", "Ultrasound\t\t2000 tk", "CT Scan\t\t3000 tk"};
    for (int i = 0; i < numTests; i++) {
        tests[i].testID = i + 1;
        strcpy(tests[i].testName, testNames[i % 5]);
        tests[i].testisBooked = false;
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

// Display booked lab tests
void displayBookedTests(struct LabTest tests[], int numTests) {
    printf("\n\tBooked Lab Tests:\n");
    for (int i = 0; i < numTests; i++) {
        if (tests[i].testisBooked) {
            printf("\n%10d. %s\n", tests[i].testID, tests[i].testName);
        }
    }
}

// Define test prices
#define BLOOD_TEST_PRICE 500
#define XRAY_PRICE 1000
#define MRI_PRICE 3000
#define ULTRASOUND_PRICE 2000
#define CTSCAN_PRICE 3000

void calculateTotalBill(struct LabTest tests[], int numTests) {
    int bloodTest = 0, xray = 0, mri = 0, ultrasound = 0, ctscan = 0;
    int totalBill = 0;
    char name[100];
    FILE *file;

    file = fopen("bill.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n\tEnter the patient's name: ");
    scanf("%s", name);

    for (int i = 0; i < numTests; i++) {
        if (tests[i].testisBooked) {
            switch (tests[i].testID) {
                case 1:
                    bloodTest++;
                    break;
                case 2:
                    xray++;
                    break;
                case 3:
                    mri++;
                    break;
                case 4:
                    ultrasound++;
                    break;
                case 5:
                    ctscan++;
                    break;
            }
        }
    }

    totalBill = (bloodTest * BLOOD_TEST_PRICE) +
                (xray * XRAY_PRICE) +
                (mri * MRI_PRICE) +
                (ultrasound * ULTRASOUND_PRICE) + (ctscan * CTSCAN_PRICE);

    fprintf(file, "\n\nPatient's name: %s\n", name);
    //fprintf(file, "Total bill:\n");
    if (bloodTest > 0) {
        fprintf(file, "Blood Test(s): %d x 500 = %d taka\n", bloodTest, bloodTest * BLOOD_TEST_PRICE);
    }
    if (xray > 0) {
        fprintf(file, "X-Ray(s): %d x 1000 = %d taka\n", xray, xray * XRAY_PRICE);
    }
    if (mri > 0) {
        fprintf(file, "MRI(s): %d x 3000 = %d taka\n", mri, mri * MRI_PRICE);
    }
    if (ultrasound > 0) {
        fprintf(file, "Ultrasound(s): %d x 2000 = %d taka\n", ultrasound, ultrasound * ULTRASOUND_PRICE);
    }
    if (ctscan > 0) {
        fprintf(file, "CT Scan(s): %d x 3000 = %d taka\n", ctscan, ctscan * CTSCAN_PRICE);
    }

    fprintf(file, "Total Bill: %d taka\n", totalBill);

    fclose(file);

    printf("\nTotal bill: %d taka\n", totalBill);
    printf("\nBill has been saved to bill.txt\n");
}

void bookTest(struct LabTest tests[], int numTests) {
    int choice;
    printf("\n\tPlease select the tests you want to book:\n");

    printf("\n\t\t1. Blood Test  (500 taka)\n");
    printf("\n\t\t2. X-Ray  (1000 taka)\n");
    printf("\n\t\t3. MRI  (3000 taka)\n");
    printf("\n\t\t4. Ultrasound  (2000 taka)\n");
    printf("\n\t\t5. CTSCAN  (3000 taka)\n");
    printf("\n\t\t6. Finish Booking\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 6) {
            system("cls");
            break;
        }

        switch (choice) {
            case 1:
                if (!tests[0].testisBooked) {
                    tests[0].testisBooked = true;
                    printf("Blood Test booked.\n");
                } else {
                    printf("Blood Test is already booked.\n");
                }
                break;
            case 2:
                if (!tests[1].testisBooked) {
                    tests[1].testisBooked = true;
                    printf("X-Ray booked.\n");
                } else {
                    printf("X-Ray is already booked.\n");
                }
                break;
            case 3:
                if (!tests[2].testisBooked) {
                    tests[2].testisBooked = true;
                    printf("MRI booked.\n");
                } else {
                    printf("MRI is already booked.\n");
                }
                break;
            case 4:
                if (!tests[3].testisBooked) {
                    tests[3].testisBooked = true;
                    printf("Ultrasound booked.\n");
                } else {
                    printf("Ultrasound is already booked.\n");
                }
                break;
            case 5:
                if (!tests[4].testisBooked) {
                    tests[4].testisBooked = true;
                    printf("CT Scan booked.\n");
                } else {
                    printf("CT Scan is already booked.\n");
                }
                break;
            default:
                printf("Invalid choice, please select a valid option.\n");
        }
    }
}

void cancelBooking(struct LabTest tests[], int numTests) {
    int choice;

    printf("\n\tPlease select the tests you want to cancel:\n");
    displayBookedTests(tests, numTests);
    printf("\n\t 6. Finish Cancellation\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 6) {
            system("cls");
            break;
        }

        switch (choice) {
            case 1:
                if (tests[0].testisBooked) {
                    tests[0].testisBooked = false;
                    printf("Blood Test cancelled.\n");
                } else {
                    printf("Blood Test is not booked.\n");
                }
                break;
            case 2:
                if (tests[1].testisBooked) {
                    tests[1].testisBooked = false;
                    printf("X-Ray cancelled.\n");
                } else {
                    printf("X-Ray is not booked.\n");
                }
                break;
            case 3:
                if (tests[2].testisBooked) {
                    tests[2].testisBooked = false;
                    printf("MRI cancelled.\n");
                } else {
                    printf("MRI is not booked.\n");
                }
                break;
            case 4:
                if (tests[3].testisBooked) {
                    tests[3].testisBooked = false;
                    printf("Ultrasound cancelled.\n");
                } else {
                    printf("Ultrasound is not booked.\n");
                }
                break;
            case 5:
                if (tests[4].testisBooked) {
                    tests[4].testisBooked = false;
                    printf("CT Scan cancelled.\n");
                } else {
                    printf("CT Scan is not booked.\n");
                }
                break;
            default:
                printf("Invalid choice, please select a valid option.\n");
        }
    }
}

int mainMenuforlabtest() {
    struct LabTest tests[MAX_TESTS];
    int choice;

    initializeLabTests(tests, MAX_TESTS);

    do {
        printf("\n\n\t\t1. View Available Lab Tests\n");
        printf("\n\t\t2. Book Tests\n");
        printf("\n\t\t3. Cancel Booking\n");
        printf("\n\t\t4. Calculate Total Bill\n");
        printf("\n\t\t5. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                displayAvailableTests(tests, MAX_TESTS);
                break;
            case 2:
                bookTest(tests, MAX_TESTS);
                break;
            case 3:
                cancelBooking(tests, MAX_TESTS);
                break;
            case 4:
                calculateTotalBill(tests, MAX_TESTS);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
