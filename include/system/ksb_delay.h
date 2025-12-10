#pragma once

#include <K1986BE92F1I.h>
#include <system/ksb_types.h>

void sys_tick_delay(size_t counter, size_t frequency_divider);

inline void delay(size_t milliseconds) {
    sys_tick_delay(milliseconds, 1000);
}

inline void delay_microseconds(size_t microseconds) {
    sys_tick_delay(microseconds, 1000 * 1000);
}