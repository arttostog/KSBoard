.syntax unified
.cpu cortex-m3
.thumb

.section .isr_vector
vectors:
.word _stack_top,
    Reset_Handler, // RESET
    base_handler,  // NMI
    base_handler,  // Hard Fault
    base_handler,  // Memory Management Fault
    base_handler,  // Bus Fault
    base_handler,  // Usage Fault
    0,
    0,
    0,
    0,
    base_handler,  // SVCall
    0,
    0,
    base_handler,  // PendSV
    base_handler,  // SysTick
    base_handler,  // CAN1
    base_handler,  // CAN2
    base_handler,  // USB
    0,
    0,
    base_handler,  // DMA
    base_handler,  // UART1
    base_handler,  // UART2
    base_handler,  // SSP1
    0,
    base_handler,  // I2C
    base_handler,  // POWER
    base_handler,  // WWDG
    0,
    base_handler,  // Timer 1
    base_handler,  // Timer 2
    base_handler,  // Timer 3
    base_handler,  // ADC
    0,
    base_handler,  // COMP
    base_handler,  // SSP2
    0,
    0,
    0,
    0,
    0,
    0,
    base_handler,  // BACKUP
    base_handler,  // EXT_INT1
    base_handler,  // EXT_INT2
    base_handler,  // EXT_INT3
    base_handler  // EXT_INT4

.section .boot, "ax"

.extern board_load
.extern board_start
.extern board_loop

.global Reset_Handler

Reset_Handler:
; Очистка bss
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0
.bss_clear_loop:
    cmp r0, r1
    beq .bss_clear_end

    str r2, [r0], #4
    blt .bss_clear_loop
.bss_clear_end:
; Копирование data
    ldr r0, =_data_start_flash
    ldr r1, =_data_start

    cmp r0, r1
    beq .data_copy_end

    ldr r2, =_data_size
    cmp r2, #0
    beq .data_copy_end
.data_copy_loop:
    ldr r3, [r0], #4
    str r3, [r1], #4
    subs r2, r2, #4
    bne .data_copy_loop
.data_copy_end:
    mov r0, #0
    mov r1, r0
    mov r2, r0
    mov r3, r0
    bl board_load

    mov r0, #0
    mov r1, r0
    bl board_start

    mov r0, #0
    mov r1, r0
.loop:
    bl board_loop
    .b loop

base_handler:
    b .
