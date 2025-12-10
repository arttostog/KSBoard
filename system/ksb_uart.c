#include <system/ksb_uart.h>

void uart_start(size_t baud_rate) {
    MDR_UART2->lcr_h |= 1 << 4 || 3 << 5;

    float baud_rate_calculated = 4000000.0f / (16 * baud_rate); // При UARTCLK == 4 МГц
    size_t baud_rate_calculated_integer = (size_t) baud_rate_calculated;

    MDR_UART2->ibrd = baud_rate_calculated_integer & 65535;
    MDR_UART2->fbrd = ((size_t) ((baud_rate_calculated - baud_rate_calculated_integer) * 64 + 0.5f)) & 63;

    MDR_UART2->cr |= 1 | 1 << 8 | 1 << 9;
}

void uart_stop() {
    MDR_UART2->cr &= ~(1 | 1 << 8 | 1 << 9);
    MDR_UART2->lcr_h &= ~(1 << 4);
}

uint8_t uart_busy() {
    return (MDR_UART2->fr >> 3) & 1;
}

void uart_write(uint8_t byte_to_write) {
    while (!uart_busy())
        continue;
    MDR_UART2->dr = (MDR_UART2->dr & ~255) | byte_to_write;
}

uint8_t uart_read() { 
    return MDR_UART2->dr & 255;
}

void uart_print(const char *text) {
    for (size_t i = 0; text[i] != '\0'; ++i)
        uart_write(text[i]);
}

void uart_println(const char *text) {
    uart_print(text);
    uart_write('\n');
}