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
    char* testNames[] = {"Blood Test\t\t\t500 tk", "X-ray\t\t\t1000 tk", "MRI\t\t\t\t3000 tk", "Ultrasound\t\t\t\t2000 tk", "CT Scan\t\t\t3000 tk"};
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

int bookTest() {
    struct LabTest tests[MAX_TESTS];
    int choice;

    // Initialize lab tests
    initializeLabTests(tests, MAX_TESTS);

    // Main menu
    do {
        printf("\n\n\t\t1.View Available Lab Tests\n");
        //printf("\n\t\t2.Book a Lab Test\n");
        //printf("\n\t\t3.Cancel Booking\n");
        printf("\n\t\t2.booking and billing\n");
        printf("\n\t\t3.Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                displayAvailableTests(tests, MAX_TESTS);
                break;
            //case 2:
               // displayAvailableTests(tests, MAX_TESTS);
               // bookTest(tests, MAX_TESTS);
                //break;
           //
            case 2:
                calculateTotalBill();
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 3);
}

#include <stdio.h>

// Define test prices
#define BLOOD_TEST_PRICE 500
#define XRAY_PRICE 1000
#define MRI_PRICE 3000
#define ULTRASOUND_PRICE 2000
#define CTSCAN_PRICE 3000
void calculateTotalBill() {
    int bloodTest = 0, xray = 0, mri = 0, ultrasound = 0, ctscan = 0;
    int choice;
    int totalBill = 0;
    char name[1000];
    FILE *file;

    file = fopen("bill.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    //printf("Welcome to the Medical Test Booking System\n");
    printf("\n\tEnter the patient's name: ");
    scanf("%s", name);
    printf("\n\tPlease select the tests you want to book:\n");

    printf("\n\t\t1. Blood Test  (500 taka)\n");
    printf("\n\t\t2. X-Ray  (1000 taka)\n");
    printf("\n\t\t3. MRI  (3000 taka)\n");
    printf("\n\t\t4. Ultrasound  (2000 taka)\n");
    printf("\n\t\t5. CTSCAN  (3000 taka)\n");
    printf("\n\t\t6. Finish Booking\n");

    while (1) {
        printf("\nEnter your choice (1-5): ");
        scanf("%d", &choice);

        if (choice == 6) {
            break;
        }

        switch (choice) {
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
            default:
                printf("Invalid choice, please select a valid option.\n");
        }
    }

    totalBill = (bloodTest * BLOOD_TEST_PRICE) +
                (xray * XRAY_PRICE) +
                (mri * MRI_PRICE) +
                (ultrasound * ULTRASOUND_PRICE) + (ctscan * CTSCAN_PRICE);


    fprintf(file, "Patient's name: %s\n",name);
    fprintf(file, "Total bill:\n");
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
        fprintf(file, "Ultrasound(s): %d x 1500 = %d taka\n", ultrasound, ultrasound * ULTRASOUND_PRICE);
    }
    if (ctscan > 0) {
        fprintf(file, "Ctscan(s): %d x 3000 = %d taka\n", ctscan, ctscan * CTSCAN_PRICE);
    }

    fprintf(file, "Total Bill: %d taka\n", totalBill);

    fclose(file);

    printf("\nTotal bill: %d taka", totalBill);
    printf("\nBill has been saved to bill.txt\n");
}




