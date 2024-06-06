#include "kernel.h"

#include "csr.h"
#include "fence_t.h"
#include "macro.h"
#include "mtime.h"
#include "trap.h"
#include "msip.h"
#include "wfi.h"

// Kernel configuration
#include "config.h"

#ifndef N_HARTS
#define N_HARTS 1
#endif /* N_HARTS */

static thread_t *sched_barrier(void)
{
	static int i = 0;
	uint64_t hartid = csrr_mhartid();

	// Increment barrier counter.
	int j = __atomic_fetch_add(&i, 1, __ATOMIC_SEQ_CST);

	// Get the next schedule
	const sched_t *sched = &schedule[(j / N_HARTS) % ARRAY_SIZE(schedule)];

	// If last to enter barrier.
	if (j % N_HARTS == N_HARTS - 1) {
		uint64_t currtime = mtime_get();
		uint64_t endtime = mtimecmp_get(hartid);
		if (currtime < endtime)
			endtime = currtime;
		endtime += sched->ticks;
		for (int i = 0; i < N_HARTS; ++i) {
			mtimecmp_set(i, endtime);
			msip_set(i);
		}
	}

	// Wait for software interrupt
	csrs_mie(MIE_MSIE);
	do {
		wfi();
	} while (!(csrr_mip() & MIP_MSIP));
	msip_clear(hartid);
	csrc_mie(MIE_MSIE);

	// Return thread to scheduler.
	return &sched->threads[hartid];
}

void kernel_init(void)
{
	csrw_mstatus(0);
	csrw_mtvec((uint64_t)trap_entry);
	csrw_cspad(cspad);
	csrw_mie(MIE_MTIE);

	// Hart 0 wakes other threads (and itself)
	if (csrr_mhartid() == 0) {
		for (int i = 0; i < N_HARTS; ++i) {
			msip_set(i);
		}
	}

	// Wait for software interrupt
	csrs_mie(MIE_MSIE);
	do {
		wfi();
	} while (!(csrr_mip() & MIP_MSIP));
	msip_clear(csrr_mhartid());
	csrc_mie(MIE_MSIE);
}

thread_t *kernel_sched(void)
{
	thread_t *thd;
	do {
		thd = sched_barrier();
		// Exit if pmp.cfg is not set (Idle).
	} while (!thd->pmp.cfg);


	/* Set PMP configuration */
	csrw_pmpcfg0(thd->pmp.cfg);
	csrw_pmpaddr0(thd->pmp.addr[0]);
	csrw_pmpaddr1(thd->pmp.addr[1]);
	csrw_pmpaddr2(thd->pmp.addr[2]);
	csrw_pmpaddr3(thd->pmp.addr[3]);
	csrw_pmpaddr4(thd->pmp.addr[4]);
	csrw_pmpaddr5(thd->pmp.addr[5]);
	csrw_pmpaddr6(thd->pmp.addr[6]);
	csrw_pmpaddr7(thd->pmp.addr[7]);
	/* Temporal fence */
	fence_t();
	return thd;
}
