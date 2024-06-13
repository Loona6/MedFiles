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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define TIME_LIMIT_HOUR 0 // Hour after which to clear appointments (0 for midnight)
#define MAX_USERNAME_LENGTH 50
// Structure to hold appointment data
typedef struct {
    char name[50];
    char contact[20];
    char date[20];
    char time[10];
    char description[100];
} Appointment;

char* create_appointment_filename(const char* username) {
    size_t filename_len = strlen(username) + strlen("_appointments.csv") + 1;
    char* filename = malloc(filename_len * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "Error allocating memory for filename.\n");
        return NULL;
    }
    snprintf(filename, filename_len, "%s_appointments.csv", username);
    return filename;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}




#define FILENAME "appointments.csv"
#define TEMP_FILENAME "temp.csv"
#define MAX_LINE_LENGTH 256

// Function to check if an appointment's date is today
int is_today(const char* date) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    char today_date[20];
    strftime(today_date, sizeof(today_date), "%Y/%m/%d", local);
    printf("Today's date: %s\n", today_date);

    return strcmp(date, today_date) == 0;
}

// Function to clear appointments in the CSV file
void clear_appointments(const char* docname) {
    FILE *file = fopen(create_appointment_filename(docname), "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen(TEMP_FILENAME, "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    // Copy the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error: file is empty.\n");
        fclose(file);
        fclose(tempFile);
        remove(TEMP_FILENAME); // Clean up temporary file
        return;
    }
    fputs(line, tempFile);

    // Process each line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line to extract the date (assuming it's in the third column)
        char temp_line[MAX_LINE_LENGTH];
        strcpy(temp_line, line);
        char *token = strtok(temp_line, ",");
        for (int i = 0; i < 2 && token != NULL; ++i) {
            token = strtok(NULL, ",");
        }
        if (token != NULL) {
            // Trim any leading/trailing whitespace from the date
            char *date = strtok(token, " \t\n");
            printf("Parsed date: %s\n", date);
            if (date != NULL && !is_today(date)) {
                fputs(line, tempFile);
            } else {
                found = 1;
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        if (remove(create_appointment_filename(docname)) != 0) {
            perror("Error deleting original file");
            return;
        }
        if (rename(TEMP_FILENAME, create_appointment_filename(docname)) != 0) {
            perror("Error renaming temporary file");
            return;
        }
        printf("Appointments removed from %s\n", create_appointment_filename(docname));
    } else {
        remove(TEMP_FILENAME);
        printf("No appointments for today found in %s.\n", create_appointment_filename(docname));
    }

    // Prompt to press Enter before clearing screen
    printf("Press Enter to continue...");
    getchar(); // Clear input buffer
    getchar(); // Wait for Enter key

    // Placeholder for screen clearing function
    // clear_screen();
}


// Function to add an appointment to the CSV file
void add_appointment(const char* username) {
    Appointment appt;

    printf("Enter patient name: ");
    fgets(appt.name, sizeof(appt.name), stdin);
    appt.name[strcspn(appt.name, "\n")] = 0; // Remove trailing newline

    printf("Enter contact information: ");
    fgets(appt.contact, sizeof(appt.contact), stdin);
    appt.contact[strcspn(appt.contact, "\n")] = 0;

    printf("Enter appointment date (YYYY-MM-DD): ");
    fgets(appt.date, sizeof(appt.date), stdin);
    appt.date[strcspn(appt.date, "\n")] = 0;

    printf("Enter appointment time (HH:MM): ");
    fgets(appt.time, sizeof(appt.time), stdin);
    appt.time[strcspn(appt.time, "\n")] = 0;

    printf("Enter appointment description: ");
    fgets(appt.description, sizeof(appt.description), stdin);
    appt.description[strcspn(appt.description, "\n")] = 0;

    char *filename = create_appointment_filename(username);
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        // Attempt to create the file
        file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            free(filename);
            return;
        }
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END); // Move to the end of the file
    int file_size = ftell(file);
    int file_just_created = (file_size == 0);

    if (file_just_created) {
        fprintf(file, "Patient Name,Contact,Date,Time,Description\n");
    }

    // Move the file pointer to the beginning if it's not at the beginning already
    if (file_size > 0) {
        fseek(file, 0, SEEK_SET);
    }

    fprintf(file, "%s,%s,%s,%s,%s\n", appt.name, appt.contact, appt.date, appt.time, appt.description);

    fclose(file);
    free(filename);
    printf("Appointment added successfully.\n");
    printf("Press Enter to continue...");
    clear_input_buffer();
    getchar(); // Wait for Enter key
}

// Function to display all appointments for a user
void display_appointments(const char* username) {
    char *filename = create_appointment_filename(username);
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[256];
        int firstLine = 1;
        printf("Current Appointments:\n\n");
        printf("%-30s%-22s%-15s%-15s%-100s\n", "Patient Name", "Contact", "Date", "Time", "Description");
        printf("-------------------------------------------------------------------------------------------------------------------\n");
        while (fgets(line, sizeof(line), file)) {
            if (firstLine) { // Skip the header line
                firstLine = 0;
                continue;
            }
            Appointment appt;
            sscanf(line, "%49[^,],%19[^,],%14[^,],%9[^,],%99[^\n]", appt.name, appt.contact, appt.date, appt.time, appt.description);
            printf("%-30s%-22s%-15s%-15s%-100s\n", appt.name, appt.contact, appt.date, appt.time, appt.description);
        }
        fclose(file);
    } else {
        perror("Error opening file");
    }
    free(filename);
    printf("Press Enter to continue...");
    clear_input_buffer();
    getchar(); // Wait for Enter key
}

// Function to edit appointments (naive approach for simplicity)
void edit_appointments(const char* username) {
    char *filename = create_appointment_filename(username);
    clear_appointments(filename);
    int numAppointments, i;

    printf("Enter the number of appointments to add: ");
    scanf("%d", &numAppointments);
    getchar(); // Consume the newline character left by scanf

    for (i = 0; i < numAppointments; i++) {
        add_appointment(username);
    }
    free(filename);
    printf("Press Enter to continue...");
    clear_input_buffer();
    getchar(); // Wait for Enter key
}
