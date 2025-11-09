#pragma once

#include <K1986BE92F1I.h>

void sys_tick_delay(bit_depth_t counter, bit_depth_t frequency_divider);

inline void delay(bit_depth_t milliseconds) {
    sys_tick_delay(milliseconds, 1000);
}

inline void delay_microseconds(bit_depth_t microseconds) {
    sys_tick_delay(microseconds, 1000 * 1000);
}