#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include "pdfgen.h"

#define BUFFER_SIZE 1024
#define LINE_WIDTH 80  // Adjust this value based on your PDF width and font size

typedef struct {
    char patient_problem[BUFFER_SIZE];
    char past_medical_history[BUFFER_SIZE];
    char drug_history[BUFFER_SIZE];
    char allergy_issues[BUFFER_SIZE];
    char on_examination[BUFFER_SIZE];
    char prognosis[BUFFER_SIZE];
    char advice[BUFFER_SIZE];
} ClinicalInfo;

// Function prototypes
void collect_info(ClinicalInfo *info);
void get_current_date(char *date_str, size_t size);
int file_exists(const char *filename);
int create_directory(const char *dirname);
int create_new_pdf(const char *filepath, ClinicalInfo *info);
void add_wrapped_text(struct pdf_doc *pdf, const char *text, int font_size, int x, int *y, int line_width);

// Function to collect clinical information from user input
void collect_info(ClinicalInfo *info) {
    printf("Patient Problem: ");
    fgets(info->patient_problem, BUFFER_SIZE, stdin);
    printf("Past Medical History: ");
    fgets(info->past_medical_history, BUFFER_SIZE, stdin);
    printf("Drug History: ");
    fgets(info->drug_history, BUFFER_SIZE, stdin);
    printf("Allergy Issues: ");
    fgets(info->allergy_issues, BUFFER_SIZE, stdin);
    printf("On Examination: ");
    fgets(info->on_examination, BUFFER_SIZE, stdin);
    printf("Prognosis: ");
    fgets(info->prognosis, BUFFER_SIZE, stdin);
    printf("Advice: ");
    fgets(info->advice, BUFFER_SIZE, stdin);

    // Remove trailing newline characters
    info->patient_problem[strcspn(info->patient_problem, "\n")] = '\0';
    info->past_medical_history[strcspn(info->past_medical_history, "\n")] = '\0';
    info->drug_history[strcspn(info->drug_history, "\n")] = '\0';
    info->allergy_issues[strcspn(info->allergy_issues, "\n")] = '\0';
    info->on_examination[strcspn(info->on_examination, "\n")] = '\0';
    info->prognosis[strcspn(info->prognosis, "\n")] = '\0';
    info->advice[strcspn(info->advice, "\n")] = '\0';
}

// Function to get the current date in YYYYMMDD format
void get_current_date(char *date_str, size_t size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date_str, size, "%04d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// Function to check if a file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int directory_exists(const char *dirname) {
    struct stat st;
    if (stat(dirname, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            return 1; // Directory exists
        } else {
            return 0; // Not a directory
        }
    } else {
        return 0; // Directory doesn't exist
    }
}

int create_directory(const char *dirname) {
    if (!directory_exists(dirname)) {
        #ifdef _WIN32
            if (_mkdir(dirname) == 0) {
                return 0; // Directory created successfully
            }
        #else
            if (mkdir(dirname, 0777) == 0) {
                return 0; // Directory created successfully
            }
        #endif
        return -1; // Failed to create directory
    }
    return 0; // Directory already exists
}

// Function to add wrapped text to the PDF
void add_wrapped_text(struct pdf_doc *pdf, const char *text, int font_size, int x, int *y, int line_width) {
    char buffer[BUFFER_SIZE];
    const char *ptr = text;
    while (strlen(ptr) > line_width) {
        strncpy(buffer, ptr, line_width);
        buffer[line_width] = '\0';
        char *last_space = strrchr(buffer, ' ');
        if (last_space) {
            *last_space = '\0';
            pdf_add_text(pdf, NULL, buffer, font_size, x, *y, PDF_BLACK);
            ptr += (last_space - buffer) + 1;
        } else {
            pdf_add_text(pdf, NULL, buffer, font_size, x, *y, PDF_BLACK);
            ptr += line_width;
        }
        *y -= 20;
    }
    pdf_add_text(pdf, NULL, ptr, font_size, x, *y, PDF_BLACK);
    *y -= 20;
}

// Function to create a new PDF file with clinical information
int create_new_pdf(const char *filepath, ClinicalInfo *info) {
    struct pdf_info pdf_info = {
        .creator = "Clinical Info System",
        .producer = "Clinical Info System",
        .title = "Clinical Information",
        .author = "Doctor",
        .subject = "Clinical Data",
        .date = "Today"
    };
    struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &pdf_info);
    if (!pdf) {
        fprintf(stderr, "Error: Failed to create PDF file %s.\n", filepath);
        return 1;
    }

    pdf_append_page(pdf);
    pdf_set_font(pdf, "Times-Roman");

    int y = 800;  // Starting y position for the title

    // Add title
    pdf_add_text(pdf, NULL, "Prescription", 16, PDF_A4_WIDTH / 2 - 50, y, PDF_BLACK);
    y -= 50;  // Move to the next section

    pdf_add_text(pdf, NULL, "Clinical Information:", 12, 50, y, PDF_BLACK);
    y -= 20;  // Move to the next line
    pdf_add_text(pdf, NULL, "Patient Problem:", 12, 50, y, PDF_BLACK);
    y -= 20;
    add_wrapped_text(pdf, info->patient_problem, 12, 50, &y, LINE_WIDTH);
    y -= 20;  // Add extra space between sections

    pdf_add_text(pdf, NULL, "Past Medical History:", 12, 50, y, PDF_BLACK);
    y -= 20;
    add_wrapped_text(pdf, info->past_medical_history, 12, 50, &y, LINE_WIDTH);
    y -= 20;

    pdf_add_text(pdf, NULL, "Drug History:", 12, 50, y, PDF_BLACK);
    y -= 20;
    add_wrapped_text(pdf, info->drug_history, 12, 50, &y, LINE_WIDTH);
    y -= 20;

    pdf_add_text(pdf, NULL, "Allergy Issues:", 12, 50, y, PDF_BLACK);
    y -= 20;
    add_wrapped_text(pdf, info->allergy_issues, 12, 50, &y, LINE_WIDTH);
    y -= 20;

    pdf_add_text(pdf, NULL, "On Examination:", 12, 50, y, PDF_BLACK);
    y -= 20;
    add_wrapped_text(pdf, info->on_examination, 12, 50, &y, LINE_WIDTH);
    y -= 20;

    pdf_add_text(pdf, NULL, "Prognosis:", 12, 50, y, PDF_BLACK);
    y -= 20;
    add_wrapped_text(pdf, info->prognosis, 12, 50, &y, LINE_WIDTH);
    y -= 20;

    pdf_add_text(pdf, NULL, "Advice:", 12, 50, y, PDF_BLACK);
    y -= 20;
    add_wrapped_text(pdf, info->advice, 12, 50, &y, LINE_WIDTH);

    pdf_save(pdf, filepath);
    pdf_destroy(pdf);
    printf("PDF file generated successfully.\n");
    return 0;
}

// Main function to handle the PDF generation process
int Pdf() {
    ClinicalInfo info;
    char patient_id[BUFFER_SIZE];
    char dirname[BUFFER_SIZE];
    char filename[BUFFER_SIZE];
    char date_str[BUFFER_SIZE];
    const char *base_directory = "C:\\Users\\maisha128\\OneDrive\\Desktop\\final final project\\MedFiles\\Clean version\\MEDFILES\\Patients";

    // Collect the patient ID
    printf("Enter patient ID: ");
    fgets(patient_id, BUFFER_SIZE, stdin);
    patient_id[strcspn(patient_id, "\n")] = '\0';

    // Generate the directory name based on base directory and patient ID
    snprintf(dirname, sizeof(dirname), "%s\\%s", base_directory, patient_id);

    // Create the directory if it doesn't exist
    if (create_directory(dirname) != 0) {
        fprintf(stderr,"Error: Failed to create directory %s.\n", dirname);
        return 1;
    }

    // Get the current date
    get_current_date(date_str, sizeof(date_str));

    // Generate filename based on patient ID and current date
    snprintf(filename, sizeof(filename), "%s\\%s_%s.pdf", dirname, patient_id, date_str);

    // Collect clinical information
    collect_info(&info);

    // Create a new PDF file
    if (create_new_pdf(filename, &info) != 0) {
        fprintf(stderr, "Error: Failed to create new PDF file %s.\n", filename);
        return 1;
    }

    return 0;
}
