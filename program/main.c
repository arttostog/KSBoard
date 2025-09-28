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
    
    port_out_config_t port_config = {
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
        0
    };

    port_out_config(MDR_PORT_D, 2, &port_config);
    digital_write(MDR_PORT_D, 2, 1);
}

void board_loop() {}