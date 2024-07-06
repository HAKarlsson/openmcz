#include "openmcz.h"
#include <string.h>

#include <stdio.h>

void setup()
{
	printf("setup zone1\r\n");
	ecall_wfi();
}

void loop()
{
	static int i = 0;
	uint64_t data;
	snprintf((char*)&data, 8, "%6x  ", i++);
	while (!ecall_send(0, &data)) ecall_yield();
	strncpy((char*)&data, "hello ", 8);
	while (!ecall_send(0, &data)) ecall_yield();
	strncpy((char*)&data, "world\r\n", 8);
	while (!ecall_send(0, &data)) ecall_yield();
}
