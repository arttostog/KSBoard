MEMORY {
    EEPROM   : ORIGIN = 0x08000000, LENGTH = 0x0001FFFF
    SRAM     : ORIGIN = 0x20000000, LENGTH = 0x00007FFF
}

_stack_size = 0x2000;

SECTIONS
{
    .boot : { KEEP(*(.isr_vector)) *(.boot) } > EEPROM
    .text : { *(.text) } > EEPROM
    
    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        . = ALIGN(4);
    } > SRAM

    .data : AT (ADDR(.text) + SIZEOF(.text)) {
        . = ALIGN(4);
        _data_start = .;
        *(.data)
        . = ALIGN(4);
        _data_end = .;
    } > SRAM
    
    .bss : {
        . = ALIGN(4);
        _bss_start = .;
        *(.bss)
        . = ALIGN(4);
        _bss_end = .;
    } > SRAM

    .stack (NOLOAD) : {
        . = ALIGN(4);
        _stack_top = .;
        . += _stack_size;
        . = ALIGN(4);
    } > SRAM

    _data_start_flash = LOADADDR(.data);
    _data_size = SIZEOF(.data);
}