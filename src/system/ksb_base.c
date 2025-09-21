#include <ksb_selected_board.h>

void delay(unsigned int milliseconds) {
    SYS_TICK->load = LSI_FREQUENCY - 1;
    SYS_TICK->val = 0;
    SYS_TICK->ctrl = SYS_TICK_CTRL_ENABLE;
    
    while (milliseconds)
        if (SYS_TICK->ctrl & SYS_TICK_CTRL_COUNTFLAG)
            --milliseconds;
    
    SYS_TICK->ctrl = 0;
}