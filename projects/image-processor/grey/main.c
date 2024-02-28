#include "../shared.h"
#include "api/openmz.h"
#include "api/util.h"

#include <stdint.h>

extern char const image[];

void setup()
{
}

void loop()
{
	shared->time = read_cycle();
	grey(shared->greyed, image, 64, 64);
	ecall_yield();
}
