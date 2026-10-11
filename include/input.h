#pragma once
struct ParseResult { long a; long b; char op; bool ok; };
ParseResult parse_expr(const char *input, int len);
