#include "altc/altio.h"
#include "api/openmz.h"

#include <stdint.h>

void setup()
{
	alt_puts("setup driver");
}

void loop()
{
	uint64_t data[3];
	data[2] = '\0';
	while (ecall_recv(0, data)) {
		alt_putstr((char *)data);
	}
	ecall_wfi();
}
