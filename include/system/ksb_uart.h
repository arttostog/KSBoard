#pragma once

#include <K1986BE92F1I.h>
#include <system/ksb_types.h>

void uart_start(size_t baud_rate);
void uart_stop();

uint8_t uart_busy();

void uart_write(uint8_t byte_to_write);
uint8_t uart_read();

void uart_print(const char *text);
void uart_println(const char *text);