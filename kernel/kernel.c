#include "kernel.h"

#include "csr.h"
#include "fence_t.h"
#include "macro.h"
#include "time.h"
#include "wfi.h"

// Kernel configuration
#include "config.h"

extern void trap_entry(void);

void kernel_init(void)
{
	csrw_mstatus(0);
	csrw_mtvec((uint64_t)trap_entry);
	csrw_cspad(cspad);
	csrw_mie(MIE_MTIE);
	kernel_yield();
}

static void kernel_wait(void)
{
	// Set new timeout time if is earlier.
	uint64_t yield_time = time_get() + yield_buffer;
	if (yield_time < timeout_get())
		timeout_set(yield_time);

	// Wait until timeout.
	while (!(csrr_mip() & MIP_MTIP))
		wfi();
}

static const sched_t *kernel_sched_next(void)
{
	static uint64_t i = 0;
	return &schedule[i++ % ARRAY_SIZE(schedule)];
}

void kernel_yield(void)
{
	// Get the next scheduling entry.
	const sched_t *sched = kernel_sched_next();

	kernel_wait();

	// Set current process and timeout.
	current = sched->zone;
	timeout_set(timeout_get() + sched->ticks);

	// Set PMP configuration
	csrw_pmpcfg0(current->pmp.cfg);
	csrw_pmpaddr0(current->pmp.addr[0]);
	csrw_pmpaddr1(current->pmp.addr[1]);
	csrw_pmpaddr2(current->pmp.addr[2]);
	csrw_pmpaddr3(current->pmp.addr[3]);
	csrw_pmpaddr4(current->pmp.addr[4]);
	csrw_pmpaddr5(current->pmp.addr[5]);
	csrw_pmpaddr6(current->pmp.addr[6]);
	csrw_pmpaddr7(current->pmp.addr[7]);
	if (sched->temporal_fence)
		fence_t();
}
