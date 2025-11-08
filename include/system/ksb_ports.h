#pragma once

#include <K1986BE92F1I.h>
#include <system/ksb_delay.h>

typedef struct {
    bit_depth_t is_output;
    bit_depth_t function;
    bit_depth_t is_digital;
    bit_depth_t enable_pull_up;
    bit_depth_t enable_pull_down;
    bit_depth_t shm_mode;
    bit_depth_t pd_mode;
    bit_depth_t power_mode;
    bit_depth_t use_filter;
} port_out_config_t;

void port_out_config(volatile mdr_port_t *port, bit_depth_t port_out, const port_out_config_t *config);

bit_depth_t digital_read(volatile mdr_port_t *port, bit_depth_t port_out);
void digital_write(volatile mdr_port_t *port, bit_depth_t port_out, bit_depth_t data);

bit_depth_t analog_read(bit_depth_t port_out);
void analog_write(bit_depth_t data);