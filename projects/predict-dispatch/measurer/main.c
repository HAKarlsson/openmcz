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

uint64_t diff(uint64_t x, uint64_t y)
{
    if (x > y)
        return x - y;
    return y - x;
}

void loop()
{
    ecall_wfi();
    uint64_t last_time = read_cycle();
    while (1) {
        ecall_wfi();
        uint64_t curr_time = read_cycle();
        uint64_t elapsed = curr_time - last_time;
        uint64_t expected = 50000000;
        alt_printf("\n\nDispatch period (deviation): %D (%D)\n", elapsed, diff(elapsed, expected));
        last_time = curr_time;
    }
}
