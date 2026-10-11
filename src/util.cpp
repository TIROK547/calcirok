#include "util.h"
static constexpr long SCALE = 1000000L;
long calc_add(long a, long b) { return (a + b) * SCALE; }
long calc_sub(long a, long b) { return (a - b) * SCALE; }
long calc_mul(long a, long b) { return a * b * SCALE; }
long calc_div(long a, long b, bool &div_zero) {
    if (b == 0) { div_zero = true; return 0; }
    div_zero = false;
    return (a * SCALE) / b;
}
