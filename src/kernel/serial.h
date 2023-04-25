#ifndef H_SERIAL
#define H_SERIAL

#include "io.h"
#include "string/string.h"

enum serial_port {
    COM1 = 0x3F8,
    COM2 = 0x2F8,
    COM3 = 0x3E8,
    COM4 = 0x2E8,
    COM5 = 0x5F8,
    COM6 = 0x4F8,
    COM7 = 0x5E8,
    COM8 = 0x4E8,
};

/* Source Code from: https://wiki.osdev.org/Serial_Ports */

static int init_serial(uint16_t port) {
    outb(port + 1, 0x00);    // Disable all interrupts
    outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(port + 1, 0x00);    //                  (hi byte)
    outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outb(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(inb(port + 0) != 0xAE) {
        return 1;
    }
    
    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(port + 4, 0x0F);
    return 0;
}

/* Reading Data */
int signal_received(uint16_t port) {
    return inb(port + 5) & 1;
}

char read_signal(uint16_t port) {
    while(signal_received(port) == 0);

    return inb(port);
}

/* Writing data */
int is_transmit_empty(uint16_t port) {
    return inb(port + 5) & 0x20;
}

void write_serial(char a, uint16_t port) {
    while (is_transmit_empty(port) == 0);

    outb(port, a);
}

void write_serial_str(const char* str, uint16_t port) {
    while (is_transmit_empty(port) == 0);

    for(int i = 0; i < strlen(str); i++) {
        outb(port, str[i]);
    }
}

#endif