#include "kernel.h"
#include "macro.h"
#include "time.h"
#include "uart.h"

// Kernel configuration
#include "config.h"

extern void trap_entry(void);


void kernel_init(void)
{
        uart_puts("starting openmz");
        csrw(mtvec, trap_entry);
        csrw(mie, 0x80);
        kernel_yield();
}

void kernel_yield(void)
{
        uint64_t yield_time = time_get() + yield_buffer;
        uint64_t deadline = timeout_get();
        if (yield_time < deadline)
                timeout_set(yield_time);
        while (!(csrr(mip) & 0x80))
                wfi();
        kernel_sched();
}

void kernel_sched(void)
{
        static int i = 0;
        sched_t sched = schedule[i];
        i = (i + 1) % ARRAY_SIZE(schedule);

        // fence.t
        temporal_fence();

        timeout_set(timeout_get() + sched.ticks);
        current = sched.zone;
        csrw(pmpcfg0, current->pmpcfg);
        csrw(pmpaddr0, current->pmpaddr[0]);
        csrw(pmpaddr1, current->pmpaddr[1]);
        csrw(pmpaddr2, current->pmpaddr[2]);
        csrw(pmpaddr3, current->pmpaddr[3]);
        csrw(pmpaddr4, current->pmpaddr[4]);
        csrw(pmpaddr5, current->pmpaddr[5]);
        csrw(pmpaddr6, current->pmpaddr[6]);
        csrw(pmpaddr7, current->pmpaddr[7]);
}
