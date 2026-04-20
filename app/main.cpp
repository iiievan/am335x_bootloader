#include <stdint.h>
#include <stdbool.h>
#include "init.h"
#include "rtt_log.h"
#include "board.hpp"


#define TAG "main"

int main ()
{
    bool init_sts = false;

    init_sts = init_board();

    if (!init_sts)
    {
        RTT_LOG_E(TAG, "Board initialization failed!");
        while (1);
    }

    RTT_LOG_I(TAG, "Board initialization seccess!");
    while(true)
    {
        delay_100us(200);
        Board::USR3.toggle();
    }

    return(0);
}