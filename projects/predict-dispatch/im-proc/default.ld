OUTPUT_ARCH(riscv)
ENTRY(_start)

__global_pointer$ = MIN(_sdata + 0x800, MAX(_data + 0x800, _end - 0x800));

MEMORY {
	RAM (rwx) : ORIGIN = 0x10008000, LENGTH = 32K
}

SECTIONS
{
        .text : {
                *(.init);
                *(.text .text.*);
        } > RAM

        .data : ALIGN(8) {
                _data = .;
                *(.data .data.*);
                _sdata = .;
                *(.sdata .sdata.*);
        } > RAM

        .bss : ALIGN(8) {
                _bss = .;
                _sbss = .;
                *(.sbss .sbss.*);
                *(.bss .bss.*);
                _end = ALIGN(8);
        } > RAM
}
