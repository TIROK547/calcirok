// ---------------------------------------------------------------------------
// io.cpp — freestanding console helpers
// ---------------------------------------------------------------------------
#include "io.h"
#include "platform.h"

void puts_raw(const char *s) {
    while (*s) plat_putc(*s++);
}

void putnl() {
    plat_putc('\r');
    plat_putc('\n');
}

void puti(long n) {
    if (n < 0) { plat_putc('-'); n = -n; }
    char buf[12];
    int i = 11;
    buf[i] = '\0';
    if (n == 0) { plat_putc('0'); return; }
    while (n > 0) { buf[--i] = (char)('0' + n % 10); n /= 10; }
    puts_raw(buf + i);
}

void putd(double n, int precision) {
    if (n < 0.0) { plat_putc('-'); n = -n; }
    long int_part = (long)n;
    puti(int_part);
    if (precision <= 0) return;
    plat_putc('.');
    double frac = n - (double)int_part;
    for (int d = 0; d < precision; ++d) {
        frac *= 10.0;
        int digit = (int)frac;
        plat_putc((char)('0' + digit));
        frac -= digit;
    }
}

int getline_raw(char *buf, int buf_len) {
    int count = 0;
    while (count < buf_len - 1) {
        char c = plat_getc();
        if (c == '\r' || c == '\n') {
            putnl();        // echo newline back
            break;
        }
        if (c == 127 || c == '\b') {   // backspace
            if (count > 0) {
                count--;
                plat_putc('\b');
                plat_putc(' ');
                plat_putc('\b');
            }
            continue;
        }
        plat_putc(c);       // echo character back
        buf[count++] = c;
    }
    buf[count] = '\0';
    return count;
}
