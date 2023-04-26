#include <stdint.h>
#include "vga/text/terminal.h"

#include "functions/utils.h"

#include "serial.h"

#define SERIAL_PORT (uint16_t)COM1

int init_serial_default() {
    return init_serial(SERIAL_PORT);
}

void kernel_early_main() {
    init_terminal();

    int serial = init_serial(SERIAL_PORT);
    if(serial == 1) {
        printf_color("ERROR: Failed to initialize serial I/O at COM1", VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    }

    write_serial_str("SERIAL INITIALIZED\r\n", SERIAL_PORT);
}

void my_epic_function(void) { }

void kernel_main() {
    write_serial_str("KERNEL_MAIN START\r\n", SERIAL_PORT);

    printf("Welcome to my Operating System!\n");
    printf_color("Wow! ", VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    printf_color("Colored text!\n", VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    printf_color("I can even change the background color!\n", VGA_COLOR_BLACK, VGA_COLOR_MAGENTA);

    printf("\nTesting ");
    printf_color("GET_FUNCTION_NAME", VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    printf(" in ");
    printf_color("functions/utils.h", VGA_COLOR_BLUE, VGA_COLOR_BLACK);
    printf(":\n");

    char* buffer = "";
    GET_FUNCTION_NAME(buffer, my_epic_function);

    printf(buffer);
    write_serial_str("KERNEL_MAIN EXIT\r\n", SERIAL_PORT);
}

void kernel_end() {
    write_serial_str("KERNEL_END START\r\n", SERIAL_PORT);
    write_serial_str("KERNEL_MAIN EXIT\r\n", SERIAL_PORT);
}