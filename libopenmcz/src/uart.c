
#ifdef PLATFORM_CHESHIRE
#include "altio.c"
#include "driver/serial/uart_16550.h"
#include <stdio.h>

static int uart_putc(char c, FILE*)
{
    return __uart_16550_putc((void*)0x03002000, c);
}

static int uart_getc(FILE*)
{
    return __uart_16550_getc((void*)0x03002000);
}

static int uart_flush(FILE*)
{
    return __uart_16550_flush((void*)0x03002000);
}

static FILE __stdio = FDEV_SETUP_STREAM(uart_putc, uart_getc, uart_flush, _FDEV_SETUP_RW);

FILE* const stdin = &__stdio;
extern FILE* const __attribute__((alias("stdin"))) stdout;
extern FILE* const __attribute__((alias("stdin"))) stderr;
#endif
