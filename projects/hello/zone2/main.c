#include "api/openmz.h"
#include "io/uart.h"

void setup()
{
	uart_puts("setup zone2");
	ecall_wfi();
}

void loop()
{
        char data[16] = "world";
        uart_puts(data);
        ecall_send(0, data);
        while (!ecall_recv(0, data))
                ecall_wfi();
        uart_puts(data);
}
