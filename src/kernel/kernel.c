#include <stdint.h>
#include "vga/text/terminal.h"
#include "serial.h"
#include "panic.h"
#include "memory/paging/paging.h"
#include "sysinfo.h"

#include "../gnu/multiboot.h"

#define SERIAL_PORT (uint16_t)COM1

int init_serial_default() {
    return init_serial(SERIAL_PORT);
}

void kernel_early_main(multiboot_info_t* mbd, uint32_t magic) {
    init_terminal();

    // Make sure the magic number is correct
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        char buffer[16];

        itoa(magic, buffer);

        printf(buffer);
        printf("\n");

        itoa(MULTIBOOT_BOOTLOADER_MAGIC, buffer);
        printf(buffer);

        panic("Invalid magic number!");
    }

    // Define SYS_MBD
    #define SYS_MBD mbd

    int serial = init_serial(SERIAL_PORT);
    if(serial == 1) {
        panic("Failed to initialize serial at I/O (COM1)");
    }

    write_serial_str("SERIAL INITIALIZED\r\n", SERIAL_PORT);
}

void kernel_main() {
    char* func_name = "";
    GET_VAR_NAME(func_name, kernel_main);

    multiboot_info_t* mbd = SYS_MBD;
    

    notify_func_entry(func_name, SERIAL_PORT);

    printf("Welcome to ");
    printf_color(SYS_NAME, VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);
    printf("!\n");

    notify_func_exit(func_name, SERIAL_PORT);
}

void kernel_end() {
    char* func_name = "";
    GET_VAR_NAME(func_name, kernel_end);

    notify_func_entry(func_name, SERIAL_PORT);

    // printf("Kernel end\n");

    notify_func_exit(func_name, SERIAL_PORT);
}