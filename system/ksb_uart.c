#include <ksboard.h>

void uart_start() {

}

void uart_stop() {

}

bit_depth_t uart_available() {
    return (MDR_UART2->fr >> 3) & 1;
}

void uart_write(char byte_to_write) {
    MDR_UART2->dr = (MDR_UART2->dr & ~255) | byte_to_write;
}

bit_depth_t uart_read() { 
    return MDR_UART2->dr & 255;
}

bit_depth_t uart_peek() {
    return 0;
}

void uart_print(const char *text) {
    for (bit_depth_t i = 0; text[i] != '\0'; ++i)
        uart_write(text[i]);
}

void uart_println(const char *text) {
    uart_print(text);
    uart_write('\n');
}