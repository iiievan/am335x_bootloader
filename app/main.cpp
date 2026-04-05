#include <stdint.h>
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
        svc_putchar('H');
    }
    else
    {
        // Вызов Undefined Instruction
        __asm__ volatile(".word 0xFFFFFFFF");

        // Вызов Data Abort (чтение из несуществующей области)
        *(volatile uint32_t*)0xFFFFFFFF;
    }

    while(true)
    {

    }

    return(0);
}