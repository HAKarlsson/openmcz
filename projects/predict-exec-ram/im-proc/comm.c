#include "api/openmz.h"

#include <stdint.h>

static uint64_t data[2];
static int i;

#define MSG_SIZE sizeof(data)

void comm_flush(void)
{
	if (i == 0)
		return;
	while (i < MSG_SIZE)
		((char *)data)[i++] = 0;
	while (!ecall_send(0, data))
		ecall_wfi();
	i = 0;
}

void comm_putchar(char c)
{
	((char *)data)[i++] = c;
	if (i >= MSG_SIZE)
		comm_flush();
}

void comm_putstr(char *s)
{
	while (*s != '\0')
		comm_putchar(*(s++));
	comm_flush();
}

void comm_puts(char *s)
{
	while (*s != '\0')
		comm_putchar(*(s++));
	comm_putchar('\n');
	comm_flush();
}
