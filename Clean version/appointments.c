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
