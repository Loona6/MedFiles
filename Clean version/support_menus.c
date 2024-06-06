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

    fprintf(file, "Patient's name: %s\n", name);
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
    char choice;
    printf("\n\tPlease select the tests you want to book:\n");

    printf("\n\t\t1. Blood Test  (500 taka)\n");
    printf("\n\t\t2. X-Ray  (1000 taka)\n");
    printf("\n\t\t3. MRI  (3000 taka)\n");
    printf("\n\t\t4. Ultrasound  (2000 taka)\n");
    printf("\n\t\t5. CTSCAN  (3000 taka)\n");
    printf("\n\t\t6. Finish Booking\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);

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
}

void cancelBooking(struct LabTest tests[], int numTests) {
    char choice;

    printf("\n\tPlease select the tests you want to cancel:\n");
    displayBookedTests(tests, numTests);
    printf("\n\t 6. Finish Cancellation\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);

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
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != '5');

    return 0;
}


struct CabinBooking {
    int vipDays;
    int generalWardDays;
    int normalCabinDays;
};

// Display booked cabins
void displayBookedCabins(struct CabinBooking booking) {
    printf("\n\n\t\t\tBooked Cabins:\n");
    if (booking.vipDays > 0) {
        printf("\t\t\t1. VIP Cabin: %d days\n", booking.vipDays);
    }
    if (booking.generalWardDays > 0) {
        printf("\t\t\t2. General Ward: %d days\n", booking.generalWardDays);
    }
    if (booking.normalCabinDays > 0) {
        printf("\t\t\t3. Normal Cabin: %d days\n", booking.normalCabinDays);
    }
}

// Book cabins
struct CabinBooking bookCabin(struct CabinBooking booking) {
    char choice;
    int days;

    printf("\n\n\t\tPlease select the type of cabin and number of days:\n");

    printf("\n\t\t\t1. VIP Cabin (5000 taka per day)\n");
    printf("\t\t\t2. General Ward (500 taka per day)\n");
    printf("\t\t\t3. Normal Cabin (1500 taka per day)\n");
    printf("\t\t\t4. Done\n");

    while (1) {
        printf("\t\t\tEnter your choice (1-4): ");
        scanf(" %c", &choice);

        if (choice == '4') {
            system("cls");
            break;
        }

        switch (choice) {
            case '1':
                printf("\t\t\tEnter number of days for VIP Cabin: ");
                scanf("%d", &days);
                booking.vipDays += days;
                break;
            case '2':
                printf("\t\t\tEnter number of days for General Ward: ");
                scanf("%d", &days);
                booking.generalWardDays += days;
                break;
            case '3':
                printf("\t\t\tEnter number of days for Normal Cabin: ");
                scanf("%d", &days);
                booking.normalCabinDays += days;
                break;
            default:
                printf("\t\t\tInvalid choice, please select a valid option.\n");
        }
    }

    return booking;
}

// Cancel cabins
struct CabinBooking cancelCabin(struct CabinBooking booking) {
    char choice;
    int days;

    printf("\n\n\t\tPlease select the type of cabin to cancel days:\n");
    displayBookedCabins(booking);
    printf("\t\t\t4. Done\n");

    while (1) {
        printf("\n\n\t\t\tEnter your choice (1-4): ");
        scanf(" %c", &choice);

        if (choice == '4') {
            system("cls");
            break;
        }

        switch (choice) {
            case '1':
                printf("\t\t\tEnter number of days to cancel for VIP Cabin: ");
                scanf("%d", &days);
                if (days <= booking.vipDays) {
                    booking.vipDays -= days;
                } else {
                    printf("\t\t\tYou cannot cancel more days than booked.\n");
                }
                break;
            case '2':
                printf("\t\t\tEnter number of days to cancel for General Ward: ");
                scanf("%d", &days);
                if (days <= booking.generalWardDays) {
                    booking.generalWardDays -= days;
                } else {
                    printf("\t\t\tYou cannot cancel more days than booked.\n");
                }
                break;
            case '3':
                printf("\t\t\tEnter number of days to cancel for Normal Cabin: ");
                scanf("%d", &days);
                if (days <= booking.normalCabinDays) {
                    booking.normalCabinDays -= days;
                } else {
                    printf("\t\t\tYou cannot cancel more days than booked.\n");
                }
                break;
            default:
                printf("\t\t\tInvalid choice, please select a valid option.\n");
        }
    }

    return booking;
}

// Calculate the total bill
void calculateCabinBill(struct CabinBooking booking) {
    int totalBill = 0;
    char name[1000];
    FILE *file;

    file = fopen("cabin_bill.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n\tEnter the patient's name: ");
    scanf("%s", name);

    totalBill = (booking.vipDays * VIP_RATE) +
                (booking.generalWardDays * GENERAL_WARD_RATE) +
                (booking.normalCabinDays * NORMAL_CABIN_RATE);

    fprintf(file, "\n\nPatient's name: %s\n", name);
    if (booking.vipDays > 0) {
        fprintf(file, "VIP Cabin: %d days x 5000 = %d taka\n", booking.vipDays, booking.vipDays * VIP_RATE);
    }
    if (booking.generalWardDays > 0) {
        fprintf(file, "General Ward: %d days x 500 = %d taka\n", booking.generalWardDays, booking.generalWardDays * GENERAL_WARD_RATE);
    }
    if (booking.normalCabinDays > 0) {
        fprintf(file, "Normal Cabin: %d days x 1500 = %d taka\n", booking.normalCabinDays, booking.normalCabinDays * NORMAL_CABIN_RATE);
    }

    fprintf(file, "Total Bill: %d taka\n", totalBill);

    fclose(file);

    printf("\nTotal bill: %d taka", totalBill);
    printf("\nBill has been saved to cabin_bill.txt\n");
}

// Main menu for cabin booking
void mainMenuforcabin() {
    struct CabinBooking booking = {0, 0, 0};
    char choice;

    do {
        printf("\n\n\t\t\t1. Book Cabin\n");
        printf("\t\t\t2. Cancel Booking\n");
        printf("\t\t\t3. Calculate Total Bill\n");
        printf("\t\t\t4. Exit\n\n");
        printf("\t\t\tEnter your choice: ");
        scanf(" %c", &choice);
        system("cls");

        switch (choice) {
            case '1':
                booking = bookCabin(booking);
                break;
            case '2':
                booking = cancelCabin(booking);
                break;
            case '3':
                calculateCabinBill(booking);
                break;
            case '4':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != '4');
}
