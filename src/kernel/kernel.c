#include <stdint.h>
#include "vga/text/terminal.h"
#include "serial.h"
#include "panic.h"
#include "memory/paging/paging.h"
#include "sysinfo.h"

#define SERIAL_PORT (uint16_t)COM1

void kernel_early_main() {
    init_terminal();

    int serial = init_serial(SERIAL_PORT);
    if(serial == 1) {
        panic("Failed to initialize serial at I/O (COM1)");
    }

    write_serial_str("SERIAL INITIALIZED\r\n", SERIAL_PORT);
}

void kernel_main() {
    char* func_name = "";
    GET_VAR_NAME(func_name, kernel_main);    

    notify_func_entry(func_name, SERIAL_PORT);

    printf("Welcome to ");
    printf_color("\n\
   _|_|_|  _|      _|    _|_|_|  _|    _|    _|_|_|  \n\
 _|    _|  _|      _|  _|_|      _|    _|  _|_|      \n\
 _|    _|    _|  _|        _|_|  _|    _|      _|_|  \n\
   _|_|_|      _|      _|_|_|      _|_|_|  _|_|_|    \n\
                                       _|            \n\
                                   _|_|              \n\
", VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);
    
    notify_func_exit(func_name, SERIAL_PORT);
}

void kernel_end() {
    char* func_name = "";
    GET_VAR_NAME(func_name, kernel_end);

    notify_func_entry(func_name, SERIAL_PORT);

    /* Code */

    notify_func_exit(func_name, SERIAL_PORT);
}