#define MB1_MAGIC    0x1BADB002
#define MB1_FLAGS    0x00000000
#define MB1_CHECKSUM (-(MB1_MAGIC + MB1_FLAGS))

__attribute__((section(".multiboot"), used))
static const unsigned int mb1_header[3] = {
    MB1_MAGIC, MB1_FLAGS, static_cast<unsigned int>(MB1_CHECKSUM),
};

extern "C" {
    unsigned char calcirok_stack[16384] __attribute__((aligned(16)));
    void plat_init();
    [[noreturn]] void calcirok_main();
}

extern "C" __attribute__((naked, section(".text._start"))) void _start() {
    asm volatile(
        "movl $(calcirok_stack + 16384), %%esp\n\t"
        "movl %%cr0, %%eax\n\t"
        "andl $0xFFFFFFF3, %%eax\n\t"
        "orl  $0x2, %%eax\n\t"
        "movl %%eax, %%cr0\n\t"
        "fninit\n\t"
        "call plat_init\n\t"
        "call calcirok_main\n\t"
        "0: hlt\n\t"
        "jmp 0b\n\t"
        ::: "eax", "memory"
    );
}
