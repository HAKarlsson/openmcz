#include "altc/altio.h"
#include "api/openmz.h"

void setup()
{
	alt_puts("setup zone2");
	ecall_wfi();
}

void loop()
{
	char data[16] = "world\n";
	alt_puts(data);
	ecall_send(0, data);
	while (!ecall_recv(0, data))
		ecall_wfi();
	alt_putstr(data);
}
