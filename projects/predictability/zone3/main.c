#include "altc/altio.h"
#include "api/openmz.h"
#include "api/util.h"

#include <stdint.h>

void setup()
{
}

void loop()
{
	uint64_t last_time = read_cycle();
        while (1) {
	        ecall_wfi();
	        uint64_t curr_time = read_cycle();
	        alt_printf("{%D}\n", (curr_time - last_time));
	        last_time = curr_time;
        }
}
