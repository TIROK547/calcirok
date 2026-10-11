// ---------------------------------------------------------------------------
// boot.cpp — Multiboot1 header + bare-metal entry point
//
// QEMU -kernel supports Multiboot1 (not Multiboot2) with 64-bit ELF.
// The header must appear in the first 8KB of the image, 4-byte aligned.
// ---------------------------------------------------------------------------
#include "platform.h"

// ---- Multiboot1 header ----------------------------------------------------

#define MB1_MAGIC    0x1BADB002
#define MB1_FLAGS    0x00000000   // no modules, no memory map needed
#define MB1_CHECKSUM (-(MB1_MAGIC + MB1_FLAGS))

__attribute__((section(".multiboot"), used))
static const unsigned int mb1_header[3] = {
    MB1_MAGIC,
    MB1_FLAGS,
    static_cast<unsigned int>(MB1_CHECKSUM),
};

// ---- entry point ----------------------------------------------------------

extern "C" [[noreturn]] void calcirok_main();

extern "C" [[noreturn]] void _start() {
    plat_init();
    calcirok_main();
}
