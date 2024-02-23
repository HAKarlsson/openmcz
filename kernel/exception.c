#include "exception.h"
#include "uart.h"

void exception_handler(uint64_t mcause, uint64_t mepc, uint64_t mtval)
{
        uart_puts("EXCEPTION");
}
