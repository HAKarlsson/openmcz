#include "kernel.h"

#include "altc/altio.h"
#include "macro.h"
#include "time.h"

// Kernel configuration
#include "config.h"

extern void trap_entry(void);

void kernel_init(void)
{
	alt_puts("starting openmz");
	csrw(mtvec, trap_entry);
	kernel_yield();
}

void kernel_wait(void)
{
	// Only enable timer interrupts.
	csrw(mie, MIE_MTIE);

	// If timeout, exit
	if (csrr(mip) & MIP_MTIP)
		return;

	// Set new timeout time if is earlier.
	uint64_t yield_time = time_get() + yield_buffer;
	if (yield_time < timeout_get())
		timeout_set(yield_time);

	// Wait until timeout.
	while (!(csrr(mip) & MIP_MTIP))
		wfi();
}

static const sched_t *kernel_sched_next(void)
{
	static int i = 0;
	return &schedule[i++ % ARRAY_SIZE(schedule)];
}

void kernel_yield(void)
{
	// Get the next scheduling entry.
	const sched_t *sched = kernel_sched_next();

	kernel_wait();
	if (sched->temporal_fence)
		temporal_fence();

	// Set current process and timeout.
	current = sched->zone;
	timeout_set(timeout_get() + sched->ticks);

	// Set PMP configuration
	csrw(pmpcfg0, current->pmp.cfg);
	csrw(pmpaddr0, current->pmp.addr[0]);
	csrw(pmpaddr1, current->pmp.addr[1]);
	csrw(pmpaddr2, current->pmp.addr[2]);
	csrw(pmpaddr3, current->pmp.addr[3]);
	csrw(pmpaddr4, current->pmp.addr[4]);
	csrw(pmpaddr5, current->pmp.addr[5]);
	csrw(pmpaddr6, current->pmp.addr[6]);
	csrw(pmpaddr7, current->pmp.addr[7]);
}
