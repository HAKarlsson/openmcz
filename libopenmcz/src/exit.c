#include "openmcz.h"

void _exit(int status)
{
    while (1)
        ecall_wfi();
}
