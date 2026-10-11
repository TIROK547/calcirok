#pragma once

// ---------------------------------------------------------------------------
// input.h — Freestanding expression parser
//
// Parses expressions of the form:  <number> <op> <number>
// Supports multi-digit integers and decimals (e.g. "12.5 + 3").
// No std::string, no heap allocation.
// ---------------------------------------------------------------------------

struct ParseResult {
    double  a;
    double  b;
    char    op;
    bool    ok;
};

// Validate and parse a null-terminated expression string.
// Returns a ParseResult; ok == false means the input was malformed.
ParseResult parse_expr(const char *input, int len);
