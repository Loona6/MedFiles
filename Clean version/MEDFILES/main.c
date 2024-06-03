#include <stdio.h>
#include <stdlib.h>

void set_console_color() {
    // ANSI escape codes to set background to white and text to black
    printf("\033[30;47m"); // 30 is black text, 47 is white background
}
int main()
{
    set_console_color();
    pri_login();
}
