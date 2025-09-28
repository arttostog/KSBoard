#include <K1986BE92F1I.h>

void board_load() {
    MDR_BKP->reg_0e |= LDO_TRIM << 8;
    MDR_BKP->reg_0f |= LSI_TRIM << 16;
    MDR_BKP->reg_0f |= HSI_TRIM << 24;

    // Назначаем везде HSI (8 МГц)
    MDR_RST_CLK->cpu_clock = 0;

    MDR_RST_CLK->uart_clock |= 1 << 25;
}