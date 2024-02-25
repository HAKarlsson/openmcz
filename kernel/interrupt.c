#include "interrupt.h"

#include "altc/altio.h"

void interrupt_handler(uint64_t mcause, uint64_t mepc, uint64_t mtval)
{
	alt_puts("INTERRUPT");
}
