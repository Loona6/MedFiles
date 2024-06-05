#include <stdio.h>

#define VIP_RATE 5000
#define GENERAL_WARD_RATE 500
#define NORMAL_CABIN_RATE 1500

struct CabinBooking {
    int vipDays;
    int generalWardDays;
    int normalCabinDays;
};

//display booked cabins
void displayBookedCabins(struct CabinBooking booking) {
    printf("\n\tBooked Cabins:\n");
    //printf("\n\tPatient's name: %s", )
    if (booking.vipDays > 0) {
        printf("\t1.VIP Cabin: %d days\n", booking.vipDays);
    }
    if (booking.generalWardDays > 0) {
        printf("\t2.General Ward: %d days\n", booking.generalWardDays);
    }
    if (booking.normalCabinDays > 0) {
        printf("\t3.Normal Cabin: %d days\n", booking.normalCabinDays);
    }
}

//book cabins
struct CabinBooking bookCabin(struct CabinBooking booking) {
    int choice, days;
    //char patientname[100];

    printf("\n\tPlease select the type of cabin and number of days:\n");
    //printf("\n\tPatient's name: ");
   // scanf("%s", patientname);

    printf("\n\t\t1. VIP Cabin (5000 taka per day)\n");
    printf("\n\t\t2. General Ward (500 taka per day)\n");
    printf("\n\t\t3. Normal Cabin (1500 taka per day)\n");
    printf("\n\t\t4. Done\n");

    while (1) {
        printf("\nEnter your choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 4) {
            system("cls");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter number of days for VIP Cabin: ");
                scanf("%d", &days);
                booking.vipDays += days;
                break;
            case 2:
                printf("Enter number of days for General Ward: ");
                scanf("%d", &days);
                booking.generalWardDays += days;
                break;
            case 3:
                printf("Enter number of days for Normal Cabin: ");
                scanf("%d", &days);
                booking.normalCabinDays += days;
                break;
            default:
                printf("Invalid choice, please select a valid option.\n");
        }
    }

    return booking;
}

//cancel cabins
struct CabinBooking cancelCabin(struct CabinBooking booking) {
    int choice, days;

    printf("\n\tPlease select the type of cabin to cancel days:\n");
    displayBookedCabins(booking);
    printf("\n\t\t4. Done\n");

    while (1) {
        printf("\nEnter your choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 4) {
            system("cls");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter number of days to cancel for VIP Cabin: ");
                scanf("%d", &days);
                if (days <= booking.vipDays) {
                    booking.vipDays -= days;
                } else {
                    printf("You cannot cancel more days than booked.\n");
                }
                break;
            case 2:
                printf("Enter number of days to cancel for General Ward: ");
                scanf("%d", &days);
                if (days <= booking.generalWardDays) {
                    booking.generalWardDays -= days;
                } else {
                    printf("You cannot cancel more days than booked.\n");
                }
                break;
            case 3:
                printf("Enter number of days to cancel for Normal Cabin: ");
                scanf("%d", &days);
                if (days <= booking.normalCabinDays) {
                    booking.normalCabinDays -= days;
                } else {
                    printf("You cannot cancel more days than booked.\n");
                }
                break;
            default:
                printf("Invalid choice, please select a valid option.\n");
        }
    }

    return booking;
}

//calculate the total bill
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
   // fprintf(file, "Total bill:\n");
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

// Main
void mainMenuforcabin() {
    struct CabinBooking booking = {0, 0, 0};
    int choice;

    do {
        printf("\n\n\t\t1. Book Cabin\n");
        printf("\n\t\t2. Cancel Booking\n");
        printf("\n\t\t3. Calculate Total Bill\n");
        printf("\n\t\t4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                booking = bookCabin(booking);
                break;
            case 2:
                booking = cancelCabin(booking);
                break;
            case 3:
                calculateCabinBill(booking);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);
}
