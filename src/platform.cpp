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
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x01);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

void plat_putc(char c) {
    while ((inb(COM1 + 5) & 0x20) == 0)
        asm volatile("pause");
    outb(COM1, static_cast<unsigned char>(c));
}

char plat_getc() {
    while ((inb(COM1 + 5) & 0x01) == 0)
        asm volatile("pause");
    return static_cast<char>(inb(COM1));
}

unsigned char plat_lsr() {
    return inb(COM1 + 5);
}
