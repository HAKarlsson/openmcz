/**
 * Driver for NS16550A UART
 */

#include "driver/serial/uart_16550.h"

typedef struct UART {
	union {
		int rhr; // receive holding register (r)
		int thr; // transmit holding register (w)
		int dll; // divisor latch least significant byte (rw)
	};
	union {
		int ier; // interrupt enable register (rw)
		int dlm; // divisor latch least significant byte (rw)
	};
	union {
		int isr; // interrupt status register (r)
		int fcr; // fifo control register (w)
	};
	int lcr; // line control register (rw)
	int mcr; // modem control register (rw)
	int lsr; // line status register (r)
	int msr; // modem status register (r)
	int spr; // scratchpad register (rw)
} UART;

// Register fields
#define LSR_DATA_READY 0x01
#define LSR_THR_EMPTY 0x20
#define LSR_TMIT_EMPTY 0x40

int __uart_16550_putc(void *base, char c)
{
	volatile UART *uart = (UART*) base;
	while (!(uart->lsr & LSR_THR_EMPTY)) {
		/* spin */
	}
	uart->thr = c;
	return c;
}

int __uart_16550_flush(void *base)
{
	volatile UART *uart = (UART*) base;
	while (!(uart->lsr & (LSR_THR_EMPTY | LSR_TMIT_EMPTY))) {
		/* spin */
	}
	return 0;
}

int __uart_16550_getc(void *base)
{
	volatile UART *uart = (UART*) base;
	while (!(uart->lsr & LSR_DATA_READY)) {
		/* loop */
	}
	return uart->rhr;
}
