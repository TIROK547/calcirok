#pragma once

// ---------------------------------------------------------------------------
// platform.h — Bare-metal I/O abstraction for calcirok
//
// Replace the bodies of these functions with GNOD / Nova console primitives.
// Nothing in this project includes <iostream>, <cstdio>, or any libc header.
// ---------------------------------------------------------------------------

// Write a single character to the console output.
void plat_putc(char c);

// Read a single character from the console (blocking).
char plat_getc();

// Initialize the platform (COM1 serial, 115200 8N1).
// Called once from _start before calcirok_main().
void plat_init();
