#include "uart.h"
#include "openmz.h"

void setup(){
        uart_puts("setup zone2");
}

void loop() {
        uart_puts("loop zone2");
        ecall_yield();
}
