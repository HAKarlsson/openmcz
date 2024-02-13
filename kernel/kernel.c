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
	// When yield takes effect.
	uint64_t yield_time = time_get() + yield_buffer;
	// Original timeout.
	uint64_t deadline = timeout_get();
	// Only update timeout if yield time is later.
	if (yield_time < deadline)
		timeout_set(yield_time);
	// Wait until timeout.
	wfi();
	kernel_sched();
}

void kernel_sched(void)
{
	// Current scheduling entry.
	static int i = 0;

	// Get the next scheduling entry.
	const sched_t *sched = &schedule[(i++) % ARRAY_SIZE(schedule)];

	// fence.t
	temporal_fence();

	// Set current process and timeout..
	current = sched->zone;
	timeout_set(timeout_get() + sched->ticks);

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
