#pragma once

#ifdef SELECTED_BOARD
    #if SELECTED_BOARD == 0xA1
        #include <./microcontrollers/K1986BE92F1I.h>
    #else
        #error SELECTED_BOARD is unknown!
    #endif
#else
    #error SELECTED_BOARD is not defined!
#endif