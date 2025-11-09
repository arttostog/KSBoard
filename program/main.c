#include <ksboard.h>
#include <fled/fled.h>

const char *text = "HELLO :)";

void board_start() {
    delay(1000);

    uart_start(9600);
    uart_println("TEST");
    delay(1000);
    char readed_byte = (char) uart_read();
    uart_write(readed_byte);
    uart_stop();
    
    fled_init(D2);
    fled_on(D2);
}

void board_loop() {}