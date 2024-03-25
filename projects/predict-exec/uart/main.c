#include "altc/altio.h"
#include "api/openmz.h"
#include "api/util.h"

#include <stdint.h>

static uint64_t end, start;
void setup()
{
}

void loop()
{
	uint64_t data[2];
	while (ecall_recv(0, data));

        ecall_recv(1,data);
        alt_printf("%D\n", data[1] - data[0]);
        ecall_yield();
}
