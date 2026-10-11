// ---------------------------------------------------------------------------
// main.cpp — calcirok freestanding entry point
//
// On bare metal this is the kernel entry (_start or equivalent).
// When built with -DCALCIROK_HOSTED it behaves as a normal main().
// ---------------------------------------------------------------------------
#include "io.h"
#include "input.h"
#include "util.h"

// Input buffer size: enough for "999999999.9 / 999999999.9\0"
static constexpr int BUF_LEN = 64;

static double dispatch(double a, double b, char op) {
    switch (op) {
        case '+': return calc_add(a, b);
        case '-': return calc_sub(a, b);
        case '*': return calc_mul(a, b);
        case '/': return calc_div(a, b);
        default:  return 0.0;
    }
}

// ---------------------------------------------------------------------------
// Bare-metal kernel entry — no argc/argv, no OS runtime.
// Rename / adjust for your specific boot environment.
// ---------------------------------------------------------------------------
extern "C" [[noreturn]] void calcirok_main() {
    puts_raw("#----------------------#"); putnl();
    puts_raw("| WELCOME TO CALCIROK! |"); putnl();
    puts_raw("#----------------------#"); putnl();
    puts_raw("  freestanding edition  "); putnl();
    putnl();

    char buf[BUF_LEN];

    while (true) {
        puts_raw(": ");
        int len = getline_raw(buf, BUF_LEN);

        if (len == 0) continue;

        ParseResult r = parse_expr(buf, len);
        if (!r.ok) {
            puts_raw("bad input — expected: <number> <+|-|*|/> <number>");
            putnl();
            continue;
        }

        // Special-case divide-by-zero reporting
        if ((r.op == '/') && (r.b == 0.0)) {
            puts_raw("error: division by zero");
            putnl();
            continue;
        }

        double result = dispatch(r.a, r.b, r.op);
        putd(result, 6);
        putnl();
    }
}

// ---------------------------------------------------------------------------
// Hosted shim: lets you build and run on Linux/macOS for dev/testing.
// CMake sets CALCIROK_HOSTED for the hosted target only.
// ---------------------------------------------------------------------------
#ifdef CALCIROK_HOSTED
int main() {
    calcirok_main();
}
#endif
