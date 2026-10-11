#pragma once

// ---------------------------------------------------------------------------
// io.h — Freestanding console helpers (no libc, no STL)
// ---------------------------------------------------------------------------

// Write a null-terminated string to the console.
void puts_raw(const char *s);

// Write a newline.
void putnl();

// Write a signed 64-bit integer as decimal text.
void puti(long n);

// Write a double as up to `precision` decimal places.
// Avoids <cstdio> / printf entirely.
void putd(double n, int precision = 6);

// Read up to (buf_len - 1) characters into buf, stopping at '\n' or '\r'.
// The buffer is always null-terminated.
// Returns number of characters read (not counting null terminator).
int getline_raw(char *buf, int buf_len);
