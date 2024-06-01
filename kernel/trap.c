#include "trap.h"

#include "ecall.h"

#include <stdbool.h>
#include <stdint.h>

enum interrupt_code {
	USER_SOFTWARE_INTERRUPT = 0,
	SUPERVISOR_SOFTWARE_INTERRUPT = 1,
	HYPERVISOR_SOFTWARE_INTERRUPT = 2,
	MACHINE_SOFTWARE_INTERRUPT = 3,
	USER_TIMER_INTERRUPT = 4,
	SUPERVISOR_TIMER_INTERRUPT = 5,
	HYPERVISOR_TIMER_INTERRUPT = 6,
	MACHINE_TIMER_INTERRUPT = 7,
	USER_EXTERNAL_INTERRUPT = 8,
	SUPERVISOR_EXTERNAL_INTERRUPT = 9,
	HYPERVISOR_EXTERNAL_INTERRUPT = 10,
	MACHINE_EXTERNAL_INTERRUPT = 11,
};

enum exception_code {
	INSTRUCTION_ADDRESS_MISALIGNED = 0,
	INSTRUCTION_ACCESS_FAULT = 1,
	ILLEGAL_INSTRUCTION = 2,
	BREAKPOINT = 3,
	LOAD_ADDRESS_MISALIGNED = 4,
	LOAD_ACCESS_FAULT = 5,
	STORE_ADDRESS_MISALIGNED = 6,
	STORE_ACCESS_FAULT = 7,
	USER_ECALL = 8,
	SUPERVISOR_ECALL = 9,
	HYPERVISOR_ECALL = 10,
	MACHINE_ECALL = 11,
	INSTRUCTION_PAGE_FAULT = 12,
	LOAD_PAGE_FAULT = 13,
	STORE_PAGE_FAULT = 15,
};

static thread_t *exception_handler(thread_t *thd, uint64_t mcause,
				   uint64_t mtval)
{
	if (mcause == USER_ECALL)
		return ecall_handler(thd);
	return thd;
}

static thread_t *interrupt_handler(thread_t *thd, uint64_t mcause,
				   uint64_t mtval)
{
	return kernel_sched();
}

thread_t *trap_handler(thread_t *thd, uint64_t mcause, uint64_t mtval)
{
	if ((int64_t)mcause < 0)
		return interrupt_handler(thd, mcause, mtval);
	return exception_handler(thd, mcause, mtval);
}
