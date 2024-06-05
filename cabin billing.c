#include <stdio.h>

#define VIP_RATE 5000
#define GENERAL_WARD_RATE 3000
#define NORMAL_CABIN_RATE 1500

void calculateCabinBill() {
    int vipDays = 0, generalWardDays = 0, normalCabinDays = 0;
    int choice, days;
    int totalBill = 0;
    char name[1000];
    FILE *file;

    file = fopen("cabin_bill.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n\tEnter the patient's name: ");
    scanf("%s", name);
    printf("\n\tPlease select the type of cabin and number of days:\n");

    printf("\n\t\t1. VIP Cabin (5000 taka per day)\n");
    printf("\n\t\t2. General Ward (3000 taka per day)\n");
    printf("\n\t\t3. Normal Cabin (1500 taka per day)\n");
    printf("\n\t\t4. Finish Booking\n");

    while (1) {
        printf("\nEnter your choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter number of days for VIP Cabin: ");
                scanf("%d", &days);
                vipDays = days;
                break;
            case 2:
                printf("Enter number of days for General Ward: ");
                scanf("%d", &days);
                generalWardDays = days;
                break;
            case 3:
                printf("Enter number of days for Normal Cabin: ");
                scanf("%d", &days);
                normalCabinDays = days;
                break;
            default:
                printf("Invalid choice, please select a valid option.\n");
        }
    }

    totalBill = (vipDays * VIP_RATE) +
                (generalWardDays * GENERAL_WARD_RATE) +
                (normalCabinDays * NORMAL_CABIN_RATE);

    fprintf(file, "Patient's name: %s\n", name);
    fprintf(file, "Total bill:\n");
    if (vipDays > 0) {
        fprintf(file, "VIP Cabin: %d days x 5000 = %d taka\n", vipDays, vipDays * VIP_RATE);
    }
    if (generalWardDays > 0) {
        fprintf(file, "General Ward: %d days x 3000 = %d taka\n", generalWardDays, generalWardDays * GENERAL_WARD_RATE);
    }
    if (normalCabinDays > 0) {
        fprintf(file, "Normal Cabin: %d days x 1500 = %d taka\n", normalCabinDays, normalCabinDays * NORMAL_CABIN_RATE);
    }

    fprintf(file, "Total Bill: %d taka\n", totalBill);

    fclose(file);

    printf("\nTotal bill: %d taka", totalBill);
    printf("\nBill has been saved to cabin_bill.txt\n");
}
