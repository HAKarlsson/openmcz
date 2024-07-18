#include "../shared.h"
#include "altio.h"
#include "openmcz.h"

#include <stdint.h>

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
    uint64_t end1 = read_cycle();
    alt_puts(shared->asciied);
    uint64_t end2 = read_cycle();
    alt_printf("%D,%D\n", end1 - shared->time, end2 - shared->time);
    ecall_yield();
}
