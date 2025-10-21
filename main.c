#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <unistd.h>
#include "pdfgen.h"

void set_console_color() {
    // ANSI escape codes to set background to white and text to black
    printf("\033[30;47m"); // 30 is black text, 47 is white background
}
int main()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = {0, 0, 1280, 840};  // Adjust dimensions as needed

    SetConsoleWindowInfo(console, TRUE, &rect);
    set_console_color();

    pri_login();
}
