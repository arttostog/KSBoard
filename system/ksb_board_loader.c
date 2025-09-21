#include <K1986BE92F1I.h>

void board_load() {
    MDR_BKP->reg_0e |= LDO_TRIM << 8;
    MDR_BKP->reg_0f |= LSI_TRIM << 16;
    MDR_BKP->reg_0f |= HSI_TRIM << 24;
}