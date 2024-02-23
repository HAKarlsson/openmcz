#pragma once
#include <stdint.h>

#define UART_BASE 0x10000000

#define UART_RBR UART_BASE + 0
#define UART_THR UART_BASE + 0
#define UART_INTERRUPT_ENABLE UART_BASE + 4
#define UART_INTERRUPT_IDENT UART_BASE + 8
#define UART_FIFO_CONTROL UART_BASE + 8
#define UART_LINE_CONTROL UART_BASE + 12
#define UART_MODEM_CONTROL UART_BASE + 16
#define UART_LINE_STATUS UART_BASE + 20
#define UART_MODEM_STATUS UART_BASE + 24
#define UART_DLAB_LSB UART_BASE + 0
#define UART_DLAB_MSB UART_BASE + 4

static inline void write_reg_u8(uintptr_t addr, uint8_t value)
{
    volatile uint8_t *loc_addr = (volatile uint8_t *)addr;
    *loc_addr = value;
}

static inline uint8_t read_reg_u8(uintptr_t addr)
{
    return *(volatile uint8_t *)addr;
}


static inline int uart_is_transmit_empty() 
{
        return read_reg_u8(UART_LINE_STATUS) & 0x20;
}

static void uart_putchar(char c)
{
        while (uart_is_transmit_empty() == 0) {};

        write_reg_u8(UART_THR, c);
}

static void uart_puts(char *s)
{
        while (*s != '\0') {
                uart_putchar(*s);
                s++;
        }
        uart_putchar('\r');
        uart_putchar('\n');
}
