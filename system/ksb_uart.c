#include <ksboard.h>

void uart_start(bit_depth_t baud_rate) {
    MDR_UART2->lcr_h |= 1 << 4 || 3 << 5;

    float baud_rate_calculated = 4000000.0f / (16 * baud_rate);
    bit_depth_t baud_rate_calculated_integer = (bit_depth_t) baud_rate_calculated;

    MDR_UART2->ibrd = baud_rate_calculated_integer & 65535;
    MDR_UART2->fbrd = ((bit_depth_t) ((baud_rate_calculated - baud_rate_calculated_integer) * 64 + 0.5f)) & 63;

    MDR_UART2->cr |= 1 | 1 << 8 | 1 << 9;
}

void uart_stop() {
    MDR_UART2->cr &= ~(1 | 1 << 8 | 1 << 9);
    MDR_UART2->lcr_h &= ~(1 << 4);
}

bit_depth_t uart_busy() {
    return (MDR_UART2->fr >> 3) & 1;
}

void uart_write(char byte_to_write) {
    while (!uart_busy())
        continue;
    MDR_UART2->dr = (MDR_UART2->dr & ~255) | byte_to_write;
}

bit_depth_t uart_read() { 
    return MDR_UART2->dr & 255;
}

void uart_print(const char *text) {
    for (bit_depth_t i = 0; text[i] != '\0'; ++i)
        uart_write(text[i]);
}

void uart_println(const char *text) {
    uart_print(text);
    uart_write('\n');
}