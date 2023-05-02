#ifndef H_PANIC
#define H_PANIC

#include "vga/text/terminal.h"

void panic(const char* message) {
    printf_color("ERROR: ", VGA_COLOR_WHITE, VGA_COLOR_RED);
    printf_color(message, VGA_COLOR_WHITE, VGA_COLOR_RED);
    asm("hlt");
}

#endif