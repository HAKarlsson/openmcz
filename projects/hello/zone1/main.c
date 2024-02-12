#include "uart.h"
#include "openmz.h"

void setup(){
        uart_puts("setup zone1");
}

void loop() {
        uart_puts("loop zone1");
        ecall_yield();
}
