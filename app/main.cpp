#include <stdint.h>
#include "init.h"
#include "board.hpp"
#include "utils.h"

int main()
{     
    init_board();
    
    for ever
    {
        delay_100us(200);
        USR_LED_3.toggle();
    }
} 

/******************************* End of file *********************************/
