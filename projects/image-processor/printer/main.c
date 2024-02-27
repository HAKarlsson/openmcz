#include "api/openmz.h"
#include "api/util.h"
#include "altc/altio.h"
#include "../shared.h"

#include <stdint.h>

void setup()
{
}


void loop()
{
        uint64_t msg[2];
        //printer(shared->asciied, 62, 30);
        ecall_recv(0, msg);
        alt_printf("cycles: %D\n", read_cycle() - msg[0]);
	ecall_yield();
}
