#include "../shared.h"
#include "altc/altio.h"
#include "api/openmz.h"
#include "api/util.h"

#include <stdint.h>

void setup()
{
}

void loop()
{
	uint64_t end1 = read_cycle();
	alt_puts(shared->asciied);
	uint64_t end2 = read_cycle();
	alt_printf("%D\t%D\n", end1 - shared->time, end2 - shared->time);
	ecall_yield();
}
