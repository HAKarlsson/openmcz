#include "altc/altio.h"

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

static void write_dec(uint64_t val)
{
	char buf[24];
	int i = 0;
	do {
		int tmp = val % 10;
		buf[i++] = ('0' + tmp);
		val /= 10;
	} while (val);
	while (i > 0)
		alt_putchar(buf[--i]);
}

static void write_hex(uint64_t val)
{
	char buf[16];
	int i = 0;
	do {
		int tmp = val & 0xF;
		buf[i++] = tmp < 10 ? ('0' + tmp) : 'A' + (tmp - 10);
		val >>= 4;
	} while (val);
	while (i > 0)
		alt_putchar(buf[--i]);
}

static int strlen(const char *s)
{
	int i = 0;
	while (s[i] != '\0') i++;
	return i;
}

void alt_printf(const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int len = strlen(fmt);
	for (int i = 0; i < len; ++i) {
		if (fmt[i] != '%') {
			alt_putchar(fmt[i]);
			continue;
		}
		switch (fmt[++i]) {
		case '%':
			alt_putchar('%');
			break;
		case 'c':
			alt_putchar(va_arg(ap, uint32_t));
			break;
		case 's':
			alt_putstr(va_arg(ap, char *));
			break;
		case 'x':
			write_hex(va_arg(ap, uint32_t));
			break;
		case 'X':
			write_hex(va_arg(ap, uint64_t));
			break;
		case 'd':
			write_dec(va_arg(ap, uint32_t));
			break;
		case 'D':
			write_dec(va_arg(ap, uint64_t));
			break;
		case '\0':
			break;
		}
	}
	va_end(ap);
}
