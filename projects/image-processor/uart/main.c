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
	alt_puts(shared->asciied);
	alt_printf("{cycles: %D}\n", read_cycle() - shared->time);
	ecall_yield();
}
