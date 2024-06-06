#include "openmcz.h"
#include <string.h>

#include <stdio.h>
#include "altio.h"

void setup()
{
	printf("setup thread1\r\n");
	ecall_wfi();
}

void loop()
{
	static int i = 0;
	char data[8];
	snprintf(data, 8, "%6x  ", i++);
	while (!ecall_send(0, data)) ecall_yield();
	strncpy(data, "hello ", 8);
	while (!ecall_send(0, data)) ecall_yield();
	strncpy(data, "world\r\n", 8);
	while (!ecall_send(0, data)) ecall_yield();
}
