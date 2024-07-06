#ifndef LIBOPENMCZ_DRIVERS_SERIAL_UART_16550_H
#define LIBOPENMCZ_DRIVERS_SERIAL_UART_16550_H

int __uart_16550_putc(void *base, char c);
int __uart_16550_getc(void *base);
int __uart_16550_flush(void *base);

#endif /* LIBOPENMCZ_DRIVERS_SERIAL_UART_16550_H */


