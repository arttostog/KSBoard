#pragma once

#include <K1986BE92F1I.h>

void board_start();
void board_loop();

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

#include "../system/ksb_delay.h"
#include "../system/ksb_port_out.h"
#include "../system/ksb_uart.h"