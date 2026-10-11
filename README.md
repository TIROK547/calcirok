# calcirok — bare-metal NOVA roottask

Freestanding C++ calculator running as a NOVA microkernel roottask.
No libc. No STL. No OS services. I/O via COM1 serial (115200 8N1).

## File structure

```
calcirok/
├── CMakeLists.txt
├── linker.ld           ← NOVA roottask load address (0x200000)
├── include/
│   ├── platform.h      ← plat_init / plat_putc / plat_getc
│   ├── io.h            ← puts_raw, putd, getline_raw
│   ├── input.h         ← ParseResult, parse_expr
│   └── util.h          ← calc_add/sub/mul/div
└── src/
    ├── boot.cpp        ← _start → plat_init() → calcirok_main()
    ├── platform.cpp    ← COM1 serial via x86 port I/O (outb/inb)
    ├── main.cpp        ← calcirok_main() [[noreturn]]
    ├── io.cpp          ← freestanding I/O helpers
    ├── input.cpp       ← expression parser
    └── util.cpp        ← arithmetic
```

## Build

Requires an x86_64 cross compiler (`x86_64-elf-g++`).

```bash
cmake -B build \
  -DCMAKE_CXX_COMPILER=x86_64-elf-g++ \
  -DCMAKE_BUILD_TYPE=MinSizeRel
cmake --build build
# output: build/calcirok  (ELF64, freestanding)
```

Load the resulting ELF as a NOVA roottask module.

## Platform layer

`platform.cpp` initialises COM1 at 115200 8N1 and exposes:

```cpp
void plat_init();        // called once from _start
void plat_putc(char c);  // spin-wait TX, write byte
char plat_getc();        // spin-wait RX, read byte
```

When GNODE is available, replace the bodies of `plat_putc` / `plat_getc`
with GNODE's console primitives and remove the `outb`/`inb` implementation.

## Input format

```
<number> <op> <number>
```

Examples (over serial terminal at 115200):
```
: 12 + 34
46.000000
: 3.14 * 2
6.280000
: 7 / 0
error: division by zero
```
