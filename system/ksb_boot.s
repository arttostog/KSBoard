.syntax unified
.cpu cortex-m3
.thumb

.section .isr_vector
vectors:
    .word _stack_bottom
    .word Reset_Handler // RESET
    .word base_handler  // NMI
    .word base_handler  // Hard Fault
    .word base_handler  // Memory Management Fault
    .word base_handler  // Bus Fault
    .word base_handler  // Usage Fault
    .word 0, 0, 0, 0
    .word base_handler  // SVCall
    .word 0, 0
    .word base_handler  // PendSV
    .word base_handler  // SysTick
    .word base_handler  // CAN1
    .word base_handler  // CAN2
    .word base_handler  // USB
    .word 0, 0
    .word base_handler  // DMA
    .word base_handler  // UART1
    .word base_handler  // UART2
    .word base_handler  // SSP1
    .word 0
    .word base_handler  // I2C
    .word base_handler  // POWER
    .word base_handler  // WWDG
    .word 0
    .word base_handler  // Timer 1
    .word base_handler  // Timer 2
    .word base_handler  // Timer 3
    .word base_handler  // ADC
    .word 0
    .word base_handler  // COMP
    .word base_handler  // SSP2
    .word 0, 0, 0, 0, 0, 0
    .word base_handler  // BACKUP
    .word base_handler  // EXT_INT1
    .word base_handler  // EXT_INT2
    .word base_handler  // EXT_INT3
    .word base_handler  // EXT_INT4

.section .boot, "ax"

.extern board_load
.extern board_start
.extern board_loop

.global Reset_Handler

Reset_Handler:
// Очистка bss
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    mov r2, #0
.bss_clear_loop:
    cmp r0, r1
    beq .bss_clear_end

    str r2, [r0], #4
    blt .bss_clear_loop
.bss_clear_end:
// Копирование data
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
    bl board_start
.loop:
    bl board_loop
    b .loop

base_handler:
    b .
