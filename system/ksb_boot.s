.syntax unified
.cpu cortex-m3
.thumb

.section .isr_vector
vectors:
    .word _stack_top
    .word entry        // RESET
    .word base_handler // NMI
    .word base_handler // Hard Fault
    .word base_handler // Memory Management Fault
    .word base_handler // Bus Fault
    .word base_handler // Usage Fault
    .word 0
    .word 0
    .word 0
    .word 0
    .word base_handler // SVCall
    .word 0
    .word 0
    .word base_handler // PendSV
    .word base_handler // SysTick
    .word base_handler // CAN1
    .word base_handler // CAN2
    .word base_handler // USB
    .word 0
    .word 0
    .word base_handler // DMA
    .word base_handler // UART1
    .word base_handler // UART2
    .word base_handler // SSP1
    .word 0
    .word base_handler // I2C
    .word base_handler // POWER
    .word base_handler // WWDG
    .word 0
    .word base_handler // Timer 1
    .word base_handler // Timer 2
    .word base_handler // Timer 3
    .word base_handler // ADC
    .word 0
    .word base_handler // COMP
    .word base_handler // SSP2
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word base_handler // BACKUP
    .word base_handler // EXT_INT1
    .word base_handler // EXT_INT2
    .word base_handler // EXT_INT3
    .word base_handler // EXT_INT4

.section .boot, "ax"

.extern board_load
.extern board_start
.extern board_loop

entry:
    bl bss_clear
    bl data_copy

    bl board_load
    bl board_start

loop:
    bl board_loop
    b loop

.thumb_func
bss_clear:
    push {r1-r3, lr}
    ldr r1, =_bss_start
    ldr r2, =_bss_end

    cmp r1, r2
    beq bss_clear_end
    mov r3, #0

bss_clear_loop:
    str r3, [r1], #4
    cmp r1, r2
    blt bss_clear_loop

bss_clear_end:
    pop {r1-r3, lr}
    bx lr

.thumb_func
data_copy:
    push {r1-r4, lr}
    ldr r1, =_data_start_flash
    ldr r2, =_data_start

    cmp r1, r2
    beq data_copy_end

    ldr r3, =_data_size
    cmp r3, #0
    beq data_copy_end

data_copy_loop:
    ldr r4, [r1], #4
    str r4, [r2], #4
    subs r3, r3, #4
    bne data_copy_loop

data_copy_end:
    pop {r1-r4, lr}
    bx lr

base_handler:
    b .
