ENTRY(_start)

MEMORY {
    RAM (rwx) : ORIGIN = 0x200000, LENGTH = 2M
}

SECTIONS {
    . = ORIGIN(RAM);

    .multiboot : {
        KEEP(*(.multiboot))     /* Multiboot1 header must be first */
    } > RAM

    .text : {
        KEEP(*(.text._start))
        *(.text .text.*)
    } > RAM

    .rodata : {
        *(.rodata .rodata.*)
    } > RAM

    .data : {
        *(.data .data.*)
    } > RAM

    .bss : {
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    } > RAM

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
        *(.note*)
        *(.gnu*)
    }
}
