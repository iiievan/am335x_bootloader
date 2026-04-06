#include <stdint.h>
#include <stdbool.h>
#include "init.h"

#define SVC_PUTCHAR    0
#define SVC_GETCHAR    1

inline void svc_putchar(char c)
{
    __asm__ volatile(
        "mov r0, %0\n\t"
        "svc %1\n\t"
        :
        : "r"(c), "I"(SVC_PUTCHAR)
        : "r0"
    );
}

int main (void)
{
    bool init_sts = false;

    init_sts = init_board();

    if (!init_sts)
    {
        while (1);
    }

    while(true)
    {

    }

    return(0);
}