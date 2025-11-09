#pragma once

#include <system/ksb_ports.h>

static const port_out_config_t FLED_PORT_OUT_CONFIG = {
    1,
    0,
    1,
    0,
    0,
    0,
    0,
    1,
    0,
};

static inline void fled_init(volatile mdr_port_t *port, bit_depth_t port_out) {
    port_out_config(port, port_out, &FLED_PORT_OUT_CONFIG);
}

static inline void fled_on(volatile mdr_port_t *port, bit_depth_t port_out) {
    digital_write(port, port_out, 1);
}

static inline void fled_off(volatile mdr_port_t *port, bit_depth_t port_out) {
    digital_write(port, port_out, 0);
}