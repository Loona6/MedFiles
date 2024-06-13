#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TESTS 5
#define MAX_NAME_LENGTH 50
#define VIP_RATE 5000
#define GENERAL_WARD_RATE 500
#define NORMAL_CABIN_RATE 1500

// Structure to represent a lab test
struct LabTest {
    int testID;
    char testName[MAX_NAME_LENGTH];
    bool testisBooked;
};

// Initialize lab tests
void initializeLabTests(struct LabTest tests[], int numTests) {
    char* testNames[] = {"Blood Test\t\t\t500 tk", "X-ray\t\t\t1000 tk", "MRI\t\t\t\t3000 tk", "Ultrasound\t\t\t2000 tk", "CT Scan\t\t\t3000 tk"};
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
    printf("\n\t\t\tPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
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
    char contactNumber[20];
    FILE *file;

    file = fopen("bill.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n\tEnter the patient's first name: ");
    scanf("%s", name);
    getchar();  // Clear input buffer
    printf("\n\tEnter the patient's contact number: ");
    scanf("%s", contactNumber);
    getchar();  // Clear input buffer

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
    fprintf(file, "Patient's contact number: %s\n", contactNumber);
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

    printf("\n\n\t\t\tTotal bill: %d taka\n", totalBill);
    printf("\n\t\t\tBill has been saved to bill.txt\n");

    // Prompt the user to press Enter to continue and clear the screen
    printf("\n\t\t\tPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
}

void bookTest(struct LabTest tests[], int numTests) {
    char choice;
    printf("\nPlease select the tests you want to book:\n");

    printf("\n\t1. Blood Test  (500 taka)\n");
    printf("\t2. X-Ray  (1000 taka)\n");
    printf("\t3. MRI  (3000 taka)\n");
    printf("\t4. Ultrasound  (2000 taka)\n");
    printf("\t5. CTSCAN  (3000 taka)\n");
    printf("\t6. Finish Booking\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);
        getchar();  // Clear input buffer

        if (choice == '6') {
            system("cls");
            break;
        }

        switch (choice) {
            case '1':
                if (!tests[0].testisBooked) {
                    tests[0].testisBooked = true;
                    printf("Blood Test booked.\n");
                } else {
                    printf("Blood Test is already booked.\n");
                }
                break;
            case '2':
                if (!tests[1].testisBooked) {
                    tests[1].testisBooked = true;
                    printf("X-Ray booked.\n");
                } else {
                    printf("X-Ray is already booked.\n");
                }
                break;
            case '3':
                if (!tests[2].testisBooked) {
                    tests[2].testisBooked = true;
                    printf("MRI booked.\n");
                } else {
                    printf("MRI is already booked.\n");
                }
                break;
            case '4':
                if (!tests[3].testisBooked) {
                    tests[3].testisBooked = true;
                    printf("Ultrasound booked.\n");
                } else {
                    printf("Ultrasound is already booked.\n");
                }
                break;
            case '5':
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

    // Prompt the user to press Enter to continue and clear the screen
    printf("\nPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
}

void cancelBooking(struct LabTest tests[], int numTests) {
    char choice;

    printf("\nPlease select the tests you want to cancel:\n");
    displayBookedTests(tests, numTests);
    printf("\n\t\t 6. Finish Cancellation\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);
        getchar();  // Clear input buffer

        if (choice == '6') {
            system("cls");
            break;
        }

        switch (choice) {
            case '1':
                if (tests[0].testisBooked) {
                    tests[0].testisBooked = false;
                    printf("Blood Test cancelled.\n");
                } else {
                    printf("Blood Test is not booked.\n");
                }
                break;
            case '2':
                if (tests[1].testisBooked) {
                    tests[1].testisBooked = false;
                    printf("X-Ray cancelled.\n");
                } else {
                    printf("X-Ray is not booked.\n");
                }
                break;
            case '3':
                if (tests[2].testisBooked) {
                    tests[2].testisBooked = false;
                    printf("MRI cancelled.\n");
                } else {
                    printf("MRI is not booked.\n");
                }
                break;
            case '4':
                if (tests[3].testisBooked) {
                    tests[3].testisBooked = false;
                    printf("Ultrasound cancelled.\n");
                } else {
                    printf("Ultrasound is not booked.\n");
                }
                break;
            case '5':
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

    // Prompt the user to press Enter to continue and clear the screen
    printf("\nPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
}

int mainMenuforlabtest() {
    struct LabTest tests[MAX_TESTS];
    char choice;

    initializeLabTests(tests, MAX_TESTS);

    do {
        printf("\n\n\n\t\t\t\t1. View Available Lab Tests\n");
        printf("\t\t\t\t2. Book Tests\n");
        printf("\t\t\t\t3. Cancel Booking\n");
        printf("\t\t\t\t4. Calculate Total Bill\n");
        printf("\t\t\t\t5. Exit\n\n");
        printf("\t\t\t\tEnter your choice: ");
        scanf(" %c", &choice);
        getchar();  // Clear input buffer
        system("cls");

        switch (choice) {
            case '1':
                displayAvailableTests(tests, MAX_TESTS);
                break;
            case '2':
                bookTest(tests, MAX_TESTS);
                break;
            case '3':
                cancelBooking(tests, MAX_TESTS);
                break;
            case '4':
                calculateTotalBill(tests, MAX_TESTS);
                break;
            case '5':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != '5');

    return 0;
}

void calculateCabinBill(int vipDays, int generalWardDays, int normalCabinDays) {
    int totalBill = 0;
    char name[100];
    char contactNumber[20];
    FILE *file;

    file = fopen("cabin_bill.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n\t\t\tEnter the patient's name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // Remove the newline character

    printf("\t\t\tEnter the patient's contact number: ");
    scanf("%s", contactNumber);
    getchar();  // To consume the newline character left by scanf

    totalBill = (vipDays * VIP_RATE) +
                (generalWardDays * GENERAL_WARD_RATE) +
                (normalCabinDays * NORMAL_CABIN_RATE);

    fprintf(file, "\n\n\t\tPatient's name: %s\n", name);
    fprintf(file, "\t\tPatient's contact number: %s\n", contactNumber);
    if (vipDays > 0) {
        fprintf(file, "\t\tVIP Cabin: %d days x 5000 = %d taka\n", vipDays, vipDays * VIP_RATE);
    }
    if (generalWardDays > 0) {
        fprintf(file, "\t\tGeneral Ward: %d days x 500 = %d taka\n", generalWardDays, generalWardDays * GENERAL_WARD_RATE);
    }
    if (normalCabinDays > 0) {
        fprintf(file, "\t\tNormal Cabin: %d days x 1500 = %d taka\n", normalCabinDays, normalCabinDays * NORMAL_CABIN_RATE);
    }

    fprintf(file, "\t\tTotal Bill: %d taka\n\n", totalBill);

    fclose(file);

    printf("\n\t\t\tTotal bill: %d taka\n", totalBill);
    printf("\t\t\tBill has been saved to cabin_bill.txt\n");

    // Prompt the user to press any key to continue and clear the screen
    printf("\n\t\t\tPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
}

void mainMenuforcabin() {
    int vipDays = 0;
    int generalWardDays = 0;
    int normalCabinDays = 0;
    int choice;

    do {
        printf("\n\n\t\t1. Calculate Total Bill for VIP Cabin (5000 tk/day)");
        printf("\n\t\t2. Calculate Total Bill for General Ward (500 tk/day)");
        printf("\n\t\t3. Calculate Total Bill for Normal Cabin (1500 tk/day)");
        printf("\n\t\t4. Exit\n");
        printf("\n\t\tEnter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character left by scanf

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        switch (choice) {
            case 1:
                printf("\n\t\t\tEnter the number of days for VIP Cabin: ");
                scanf("%d", &vipDays);
                getchar();  // To consume the newline character left by scanf
                calculateCabinBill(vipDays, 0, 0);
                break;
            case 2:
                printf("\n\t\t\tEnter the number of days for General Ward: ");
                scanf("%d", &generalWardDays);
                getchar();  // To consume the newline character left by scanf
                calculateCabinBill(0, generalWardDays, 0);
                break;
            case 3:
                printf("\n\t\t\tEnter the number of days for Normal Cabin: ");
                scanf("%d", &normalCabinDays);
                getchar();  // To consume the newline character left by scanf
                calculateCabinBill(0, 0, normalCabinDays);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("\\n\t\t\t\Invalid choice. Please enter a number between 1 and 4.\n");
        }

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

    } while (choice != 4);
}

void viewLabTestBillingHistory() {
    FILE *file;
    char line[1000];

    file = fopen("bill.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("\n\t\t\tPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
    printf("\n\t\t\tLab Test Billing History:\n\n\n");
    while (fgets(line, sizeof(line), file)) {
        printf("\t\t%s", line);
    }
    printf("\n\t\t\tPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
    fclose(file);
}

void viewCabinBillingHistory() {
    FILE *file;
    char line[1000];

    file = fopen("cabin_bill.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("\n\t\t\tPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
    printf("\n\t\t\tCabin Billing History:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("\n\t\t\tPress Enter to continue...");
    getchar();  // Wait for user input
    system("cls");
    fclose(file);
}

void viewBillingHistory() {
    int choice;

    do {
        printf("\n\t\t\t1. View Lab Test Billing History\n");
        printf("\t\t\t2. View Cabin Billing History\n");
        printf("\t\t\t3. Back to Main Menu\n");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear input buffer

        switch (choice) {
            case 1:
                viewLabTestBillingHistory();
                break;
            case 2:
                viewCabinBillingHistory();
                break;
            case 3:
                printf("\n\n\t\tReturning to Main Menu...\n");
                break;
            default:
                printf("\t\t\tInvalid choice. Please enter a number between 1 and 3.\n");
        }
    } while (choice != 3);
}
