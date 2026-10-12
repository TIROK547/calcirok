#include "../include/io.h"
#include "../include/platform.h"

void puts_raw(const char *s) {
  while (*s)
    plat_putc(*s++);
}
void putnl() {
  plat_putc('\r');
  plat_putc('\n');
}
static void puti(long n) {
  if (n < 0) {
    plat_putc('-');
    n = -n;
  }
  char buf[12];
  int i = 11;
  buf[i] = '\0';
  if (n == 0) {
    plat_putc('0');
    return;
  }
  while (n > 0) {
    buf[--i] = (char)('0' + n % 10);
    n /= 10;
  }
  puts_raw(buf + i);
}
void put_fixed(long val) {
  if (val < 0) {
    plat_putc('-');
    val = -val;
  }
  puti(val / 1000000L);
  plat_putc('.');
  char buf[7];
  buf[6] = '\0';
  long frac = val % 1000000L;
  for (int i = 5; i >= 0; --i) {
    buf[i] = (char)('0' + frac % 10);
    frac /= 10;
  }
  puts_raw(buf);
}
int getline_raw(char *buf, int buf_len) {
  int count = 0;
  while (count < buf_len - 1) {
    char c = plat_getc();
    if (c == '\r') {
      putnl();
      if (plat_lsr() & 0x01) {
        char next = plat_getc();
        if (next != '\n')
          buf[count++] = next;
      }
      break;
    }
    if (c == '\n') {
      putnl();
      break;
    }
    if (c == 127 || c == '\b') {
      if (count > 0) {
        count--;
        plat_putc('\b');
        plat_putc(' ');
        plat_putc('\b');
      }
      continue;
    }
    plat_putc(c);
    buf[count++] = c;
  }
  buf[count] = '\0';
  return count;
}
