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
	uint64_t msg[2];
	msg[0] = read_cycle();
	ecall_send(0, msg);
	grey(shared->greyed, image, 64, 64);
	ecall_yield();
}
