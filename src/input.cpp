// ---------------------------------------------------------------------------
// input.cpp — Freestanding expression parser
//
// Grammar (no spaces required, but allowed):
//   expr  ::= number op number
//   number ::= ['-'] digit+ ['.' digit+]
//   op    ::= '+' | '-' | '*' | '/'
//
// Handles multi-digit, decimal numbers; negative operands NOT supported
// (the '-' character is reserved as an operator).
// ---------------------------------------------------------------------------
#include "input.h"

// ---- helpers ---------------------------------------------------------------

static bool is_digit(char c)  { return c >= '0' && c <= '9'; }
static bool is_space(char c)  { return c == ' ' || c == '\t'; }
static bool is_op(char c)     {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Parse a non-negative decimal number starting at input[pos].
// Advances pos past the number. Returns false if no digits found.
static bool parse_number(const char *input, int len, int &pos, double &out) {
    // skip leading spaces
    while (pos < len && is_space(input[pos])) ++pos;

    if (pos >= len || !is_digit(input[pos])) return false;

    long long int_part = 0;
    while (pos < len && is_digit(input[pos])) {
        int_part = int_part * 10 + (input[pos] - '0');
        ++pos;
    }

    double frac = 0.0;
    if (pos < len && input[pos] == '.') {
        ++pos;  // consume '.'
        double place = 0.1;
        while (pos < len && is_digit(input[pos])) {
            frac += (input[pos] - '0') * place;
            place *= 0.1;
            ++pos;
        }
    }

    out = static_cast<double>(int_part) + frac;
    return true;
}

// ---- public ----------------------------------------------------------------

ParseResult parse_expr(const char *input, int len) {
    ParseResult r{0.0, 0.0, ' ', false};
    int pos = 0;

    if (!parse_number(input, len, pos, r.a)) return r;

    // skip spaces before op
    while (pos < len && is_space(input[pos])) ++pos;

    if (pos >= len || !is_op(input[pos])) return r;
    r.op = input[pos++];

    if (!parse_number(input, len, pos, r.b)) return r;

    // skip trailing spaces; must be at end
    while (pos < len && is_space(input[pos])) ++pos;
    if (pos != len) return r;   // trailing garbage

    r.ok = true;
    return r;
}
