#include <ksboard.h>

const char *text = "HELLO :)";

void board_start() {
    delay(1000);
    uart_start(9600);
    uart_println("TEST");
    delay(1000);
    char readed_byte = (char) uart_read();
    uart_write(readed_byte);
    uart_stop();
}

void board_loop() {}