#pragma once

#include <ksb_selected_board.h>

void board_start();
void board_loop();

void delay(unsigned int milliseconds);

typedef struct {
    unsigned int is_output;
    unsigned int function;
    unsigned int is_digital;
    unsigned int enable_pull_up;
    unsigned int enable_pull_down;
    unsigned int shm_mode;
    unsigned int pd_mode;
    unsigned int power_mode;
    unsigned int use_filter;
} pin_config_t;

void pin_config(volatile mdr_port_t *port, unsigned int port_out,  const pin_config_t *config);

unsigned int pin_digital_read(volatile mdr_port_t *port, unsigned int port_out);
void pin_digital_write(volatile mdr_port_t *port, unsigned int port_out, unsigned int data);

unsigned int pin_analog_read(volatile mdr_port_t *port, unsigned int port_out);
void pin_analog_write(volatile mdr_port_t *port, unsigned int port_out, unsigned int data);