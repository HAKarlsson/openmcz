#include "openmcz.h"

#include <stdio.h>

void setup()
{
	printf("setup zone2\r\n");
	ecall_wfi();
}

void loop()
{
	uint64_t data[2] = {0};
	while (ecall_recv(0, data))
		printf("%s", (char*)data);
	ecall_yield();
}
