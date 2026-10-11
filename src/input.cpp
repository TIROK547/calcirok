#include "input.h"
static bool is_digit(char c) { return c >= '0' && c <= '9'; }
static bool is_space(char c) { return c == ' ' || c == '\t'; }
static bool is_op(char c)    { return c=='+' || c=='-' || c=='*' || c=='/'; }
static bool parse_number(const char *in, int len, int &pos, long &out) {
    while (pos < len && is_space(in[pos])) ++pos;
    if (pos >= len || !is_digit(in[pos])) return false;
    long n = 0;
    while (pos < len && is_digit(in[pos])) n = n * 10 + (in[pos++] - '0');
    out = n; return true;
}
ParseResult parse_expr(const char *input, int len) {
    ParseResult r{0, 0, ' ', false}; int pos = 0;
    if (!parse_number(input, len, pos, r.a)) return r;
    while (pos < len && is_space(input[pos])) ++pos;
    if (pos >= len || !is_op(input[pos])) return r;
    r.op = input[pos++];
    if (!parse_number(input, len, pos, r.b)) return r;
    while (pos < len && is_space(input[pos])) ++pos;
    if (pos != len) return r;
    r.ok = true; return r;
}
