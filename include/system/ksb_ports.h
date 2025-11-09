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

#define A0 MDR_PORT_A, 0
#define A1 MDR_PORT_A, 1
#define A2 MDR_PORT_A, 2
#define A3 MDR_PORT_A, 3
#define A4 MDR_PORT_A, 4
#define A5 MDR_PORT_A, 5
#define A6 MDR_PORT_A, 6
#define A7 MDR_PORT_A, 7
#define A8 MDR_PORT_A, 8
#define A9 MDR_PORT_A, 9
#define A10 MDR_PORT_A, 10
#define A11 MDR_PORT_A, 11
#define A12 MDR_PORT_A, 12
#define A13 MDR_PORT_A, 13
#define A14 MDR_PORT_A, 14
#define A15 MDR_PORT_A, 15

#define B0 MDR_PORT_B, 0
#define B1 MDR_PORT_B, 1
#define B2 MDR_PORT_B, 2
#define B3 MDR_PORT_B, 3
#define B4 MDR_PORT_B, 4
#define B5 MDR_PORT_B, 5
#define B6 MDR_PORT_B, 6
#define B7 MDR_PORT_B, 7
#define B8 MDR_PORT_B, 8
#define B9 MDR_PORT_B, 9
#define B10 MDR_PORT_B, 10
#define B11 MDR_PORT_B, 11
#define B12 MDR_PORT_B, 12
#define B13 MDR_PORT_B, 13
#define B14 MDR_PORT_B, 14
#define B15 MDR_PORT_B, 15

#define C0 MDR_PORT_C, 0
#define C1 MDR_PORT_C, 1
#define C2 MDR_PORT_C, 2
#define C3 MDR_PORT_C, 3
#define C4 MDR_PORT_C, 4
#define C5 MDR_PORT_C, 5
#define C6 MDR_PORT_C, 6
#define C7 MDR_PORT_C, 7
#define C8 MDR_PORT_C, 8
#define C9 MDR_PORT_C, 9
#define C10 MDR_PORT_C, 10
#define C11 MDR_PORT_C, 11
#define C12 MDR_PORT_C, 12
#define C13 MDR_PORT_C, 13
#define C14 MDR_PORT_C, 14
#define C15 MDR_PORT_C, 15

#define D0 MDR_PORT_D, 0
#define D1 MDR_PORT_D, 1
#define D2 MDR_PORT_D, 2
#define D3 MDR_PORT_D, 3
#define D4 MDR_PORT_D, 4
#define D5 MDR_PORT_D, 5
#define D6 MDR_PORT_D, 6
#define D7 MDR_PORT_D, 7
#define D8 MDR_PORT_D, 8
#define D9 MDR_PORT_D, 9
#define D10 MDR_PORT_D, 10
#define D11 MDR_PORT_D, 11
#define D12 MDR_PORT_D, 12
#define D13 MDR_PORT_D, 13
#define D14 MDR_PORT_D, 14
#define D15 MDR_PORT_D, 15

#define E0 MDR_PORT_E, 0
#define E1 MDR_PORT_E, 1
#define E2 MDR_PORT_E, 2
#define E3 MDR_PORT_E, 3
#define E4 MDR_PORT_E, 4
#define E5 MDR_PORT_E, 5
#define E6 MDR_PORT_E, 6
#define E7 MDR_PORT_E, 7
#define E8 MDR_PORT_E, 8
#define E9 MDR_PORT_E, 9
#define E10 MDR_PORT_E, 10
#define E11 MDR_PORT_E, 11
#define E12 MDR_PORT_E, 12
#define E13 MDR_PORT_E, 13
#define E14 MDR_PORT_E, 14
#define E15 MDR_PORT_E, 15

#define F0 MDR_PORT_F, 0
#define F1 MDR_PORT_F, 1
#define F2 MDR_PORT_F, 2
#define F3 MDR_PORT_F, 3
#define F4 MDR_PORT_F, 4
#define F5 MDR_PORT_F, 5
#define F6 MDR_PORT_F, 6
#define F7 MDR_PORT_F, 7
#define F8 MDR_PORT_F, 8
#define F9 MDR_PORT_F, 9
#define F10 MDR_PORT_F, 10
#define F11 MDR_PORT_F, 11
#define F12 MDR_PORT_F, 12
#define F13 MDR_PORT_F, 13
#define F14 MDR_PORT_F, 14
#define F15 MDR_PORT_F, 15