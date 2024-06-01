#include <sys/stat.h>

#define UART_BASE 0x03002000

static void uart_putc(char c)
{
	volatile char* thr = (char*)UART_BASE;
	volatile char* line_status = (char*)(UART_BASE + 20);
	while (!(*line_status & 0x20)) {}
	*thr = c;
}

int _fstat(int file, struct stat* st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(const char* name, int flags, int mode)
{
    return -1;
}

int _write(int file, char* c, int len)
{
	for (int i = 0; i < len; ++i) {
		if (c[i] == '\n')
			uart_putc('\r');
		uart_putc(c[i]);
	}
	return len;
}

int _read(int file, char* c, int len)
{
    return -1;
}

char* _sbrk(int incr)
{
    extern char _end; /* Defined by the linker */
    static char* heap_ptr = &_end;
    char* base = heap_ptr;
    heap_ptr += incr;
    return base;
}
