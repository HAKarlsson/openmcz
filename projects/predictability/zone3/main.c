#include "altc/altio.h"
#include "api/openmz.h"
#include "api/util.h"

#include <stdint.h>

void setup()
{
	alt_puts("setup measurer");
}

void loop()
{
	static uint64_t last_time = 0;
	uint64_t curr_time = read_cycle();
	alt_printf("{%D}", (curr_time - last_time));
	last_time = curr_time;
	ecall_wfi();
}
