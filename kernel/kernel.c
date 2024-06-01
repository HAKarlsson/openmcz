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
#endif

void wait_for_msi(void)
{
	csrs_mie(MIE_MSIE);
	while (!(csrr_mip() & MIP_MSIP))
		wfi();
	msip_clear(csrr_mhartid());
	csrc_mie(MIE_MSIE);
}

void kernel_init(void)
{
	csrw_mstatus(0);
	csrw_mtvec((uint64_t)trap_entry);
	csrw_cspad(cspad);
	csrw_mie(MIE_MTIE);

	if (csrr_mhartid() == 0) {
		uint64_t start_time = mtime_get() + 1000000;
		for (int i = 0; i < N_HARTS; ++i) {
			mtimecmp_set(i, start_time);
			msip_set(i);
		}
	}

	wait_for_msi();

	while (!(csrr_mie() & MIP_MTIP))
		wfi();
}

const sched_t *get_next_sched(uint64_t hartid)
{
	static int i[N_HARTS] = {0};
	return &schedule[(i[hartid]++) % ARRAY_SIZE(schedule)];
}

thread_t *kernel_sched(void)
{
	uint64_t hartid = csrr_mhartid();
	// Get the next scheduling entry.
	const sched_t *sched = get_next_sched(hartid);
	
	thread_t *thd = &sched->threads[hartid];

	mtimecmp_set(hartid, mtimecmp_get(hartid) + sched->ticks);

	// Set PMP configuration
	csrw_pmpcfg0(thd->pmp.cfg);
	csrw_pmpaddr0(thd->pmp.addr[0]);
	csrw_pmpaddr1(thd->pmp.addr[1]);
	csrw_pmpaddr2(thd->pmp.addr[2]);
	csrw_pmpaddr3(thd->pmp.addr[3]);
	csrw_pmpaddr4(thd->pmp.addr[4]);
	csrw_pmpaddr5(thd->pmp.addr[5]);
	csrw_pmpaddr6(thd->pmp.addr[6]);
	csrw_pmpaddr7(thd->pmp.addr[7]);

	if (sched->temporal_fence)
		fence_t();
	return thd;
}
