#include "openmcz.h"

#include <stdio.h>

void setup()
{
	printf("setup zone2\r\n");
	ecall_wfi();
}

void loop()
{
	char data[9];
	data[8] = '\0';
	while (ecall_recv(0, data))
		printf("%s", data);
	ecall_yield();
}
