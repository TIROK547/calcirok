// ---------------------------------------------------------------------------
// platform.cpp — x86 COM1 serial, 115200 8N1
// ---------------------------------------------------------------------------
#include "platform.h"

static inline void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

static inline unsigned char inb(unsigned short port) {
    unsigned char val;
    asm volatile("inb %1, %0" : "=a"(val) : "Nd"(port) : "memory");
    return val;
}

static constexpr unsigned short COM1 = 0x3F8;

void plat_init() {
    outb(COM1 + 1, 0x00);   // disable interrupts
    outb(COM1 + 3, 0x80);   // DLAB on
    outb(COM1 + 0, 0x01);   // baud lo: divisor 1 = 115200
    outb(COM1 + 1, 0x00);   // baud hi
    outb(COM1 + 3, 0x03);   // 8N1, DLAB off
    outb(COM1 + 2, 0xC7);   // FIFO on, clear, 14-byte threshold
    outb(COM1 + 4, 0x0B);   // RTS + DTR + OUT2 (enables IRQ line, needed by some emulators)
}

void plat_putc(char c) {
    // wait for transmit holding register empty (bit 5)
    while ((inb(COM1 + 5) & 0x20) == 0)
        asm volatile("pause");
    outb(COM1, static_cast<unsigned char>(c));
}

char plat_getc() {
    // wait for data ready (bit 0)
    while ((inb(COM1 + 5) & 0x01) == 0)
        asm volatile("pause");
    return static_cast<char>(inb(COM1));
}
