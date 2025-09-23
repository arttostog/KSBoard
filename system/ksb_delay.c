#include <ksboard.h>

static void sys_tick_delay(bit_depth_t counter, bit_depth_t frequency_divider) {
    // Высчитывается исходя из HCLK, который настроен на источник HSI
    SYS_TICK->load = (HSI_FREQUENCY / frequency_divider) - 1;
    SYS_TICK->val = 0;
    SYS_TICK->ctrl = 1 | 1 << 2;

    while (counter)
        if (SYS_TICK->ctrl & 1 << 16)
            --counter;
    
    SYS_TICK->ctrl = 0;
}

void delay(bit_depth_t milliseconds) {
    sys_tick_delay(milliseconds, 1000);
}

void delay_microseconds(bit_depth_t microseconds) {
    sys_tick_delay(microseconds, 1000 * 1000);
}