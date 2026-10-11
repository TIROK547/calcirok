#include "io.h"
#include "input.h"
#include "util.h"

static constexpr int BUF_LEN = 64;

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
        if (!r.ok) { puts_raw("bad input — use: <int> <+|-|*|/> <int>"); putnl(); continue; }
        if (r.op == '/') {
            bool dz = false;
            long res = calc_div(r.a, r.b, dz);
            if (dz) { puts_raw("error: division by zero"); putnl(); continue; }
            put_fixed(res);
        } else {
            long res = r.op=='+' ? calc_add(r.a,r.b) : r.op=='-' ? calc_sub(r.a,r.b) : calc_mul(r.a,r.b);
            put_fixed(res);
        }
        putnl();
    }
}
