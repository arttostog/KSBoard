#include <system/ksb_delay.h>

void sys_tick_delay(size_t counter, size_t frequency_divider) {
    // Высчитывается исходя из HCLK, который настроен на источник HSI
    SYS_TICK->load = (HSI_FREQUENCY / frequency_divider) - 1;
    SYS_TICK->val = 0;
    SYS_TICK->ctrl = 1 | 1 << 2;

    while (counter)
        if (SYS_TICK->ctrl & 1 << 16)
            --counter;
    
    SYS_TICK->ctrl = 0;
}