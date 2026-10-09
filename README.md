# calcirok

A small command-line calculator written in C++17. It reads one expression of
the form `<number><operation><number>`, prints the result, and repeats until
you quit.

## Build

Requires a C++17 compiler (g++ or clang++).

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 -o calcirok main.cpp user_input_utils.cpp util.cpp
```

To catch memory bugs and undefined behavior while developing, add
`-fsanitize=address,undefined` and drop `-O2`.

## Run

```sh
./calcirok
```

```text
#----------------------#
| WELCOME TO CALCIROK! |
#----------------------#
what do you want to get calculated?(+, -, /, *; q to quit)
: 12+34
46
what do you want to get calculated?(+, -, /, *; q to quit)
: 10 / 4
2.5
what do you want to get calculated?(+, -, /, *; q to quit)
: 10/0
can't calculate that (division by zero or result too large).
what do you want to get calculated?(+, -, /, *; q to quit)
: q
```

Quit with `q`, `quit`, `exit`, or Ctrl+D.

## Input rules

- Exactly two whole, non-negative numbers and one operator: `+`, `-`, `*`, `/`.
- Spaces and tabs are ignored, so `5 + 3` and `5+3` are the same.
- Anything else prints a hint and asks again.

## Limitations

- No decimals, negative numbers, parentheses, or chained operations
  (`1+2+3` is rejected).
- Numbers are stored as `double`, so results are accurate to about 15
  significant digits; larger results print in scientific notation.
- Division by zero and results too large to represent are reported as errors.

## Project layout

| File | Purpose |
|---|---|
| `main.cpp` | Input loop and output |
| `user_input_utils.h/.cpp` | Reading a line, validating it, parsing it |
| `util.h/.cpp` | Arithmetic functions and `calculate` |
