#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



typedef struct {
    char name[50];
    char contact[12];
    char age[3];
    char gender[7];
    char date[11]; // Assuming date is stored as "YYYY-MM-DD"
} Patient;

