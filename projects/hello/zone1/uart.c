#include "uart.h"

volatile char *const uart_txdata = (char*)0x10000000;
volatile char *const uart_line_status = (char*)0x10000014;

void uart_putchar(char c)
{
        while ((*uart_line_status & 0x20) == 0) {
        }
        *uart_txdata = c;
}

void uart_puts(char *s)
{
        while (*s != '\0') {
                uart_putchar(*s);
                s++;
        }
        uart_putchar('\r');
        uart_putchar('\n');
}
