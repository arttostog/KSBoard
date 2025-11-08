#pragma once

#include <K1986BE92F1I.h>

void uart_start(bit_depth_t baud_rate);
void uart_stop();

bit_depth_t uart_busy();

void uart_write(char byte_to_write);
bit_depth_t uart_read();

void uart_print(const char *text);
void uart_println(const char *text);