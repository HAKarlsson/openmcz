#include "../shared.h"
#include "openmcz.h"

#include <stdint.h>

extern char const image[];

uint64_t read_cycle()
{
    uint64_t val;
    __asm__ volatile("csrr x0,cycle"
                     : "=r"(val));
    return val;
}

void setup()
{
}

void loop()
{
    shared->time = read_cycle();
    grey(shared->greyed, image, 64, 64);
    ecall_yield();
}
