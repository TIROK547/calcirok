#pragma once

// ---------------------------------------------------------------------------
// platform.h — Bare-metal I/O abstraction for calcirok
// ---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void plat_init();
void plat_putc(char c);
char plat_getc();
unsigned char plat_lsr();

#ifdef __cplusplus
}
#endif
