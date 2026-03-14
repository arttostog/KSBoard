ENTRY(Reset_Handler)
MEMORY {
    EEPROM   : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM     : ORIGIN = 0x20000000, LENGTH = 32K
}

_stack_size = 4K;

SECTIONS
{
    .text : {
        KEEP(*(.isr_vector))
        *(.boot*)
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > EEPROM

    .data : {
        _data_start = .;
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } > SRAM AT > EEPROM

    _data_start_flash = LOADADDR(.data);
    
    .bss : {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
    } > SRAM

    .stack (NOLOAD) : {
        . = ALIGN(8);
        . += _stack_size;
        . = ALIGN(8);
        _stack_top = .;
    } > SRAM
}