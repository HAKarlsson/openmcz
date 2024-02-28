#include "exception.h"

#include "altc/altio.h"

void exception_handler(uint64_t mcause, uint64_t mepc, uint64_t mtval)
{
	alt_puts("EXCEPTION");
	while (1)
		;
}
