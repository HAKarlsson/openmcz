#include "altc/altio.h"
#include "altc/uart.h"

#include <stdarg.h>

int alt_putchar(char c)
{
	uart_putchar(c);
	return c;
}

int alt_putstr(const char *str)
{
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == '\n')
			alt_putchar('\r');
		alt_putchar(str[i]);
		i++;
	}
	return i;
}

int alt_puts(const char *str)
{
	int i = alt_putstr(str);
	alt_putchar('\r');
	alt_putchar('\n');
	return i;
}
