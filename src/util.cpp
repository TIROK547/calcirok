// ---------------------------------------------------------------------------
// util.cpp — Arithmetic operations. Zero dependencies.
// ---------------------------------------------------------------------------
#include "util.h"

double calc_add(double a, double b) { return a + b; }
double calc_sub(double a, double b) { return a - b; }
double calc_mul(double a, double b) { return a * b; }

double calc_div(double a, double b) {
    if (b == 0.0) return 0.0;   // caller can check; no exception available
    return a / b;
}
