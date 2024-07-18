#include "openmcz.h"
#include <stdint.h>

int ecall_yield(void)
{
    register uint64_t a7 __asm__("a7");
    register uint64_t a0 __asm__("a0");
    a7 = 0;
    __asm__ volatile("ecall"
                     : "=r"(a0)
                     : "r"(a7));
    return a0;
}

int ecall_wfi(void)
{
    register uint64_t a7 __asm__("a7");
    register uint64_t a0 __asm__("a0");
    a7 = 1;
    __asm__ volatile("ecall"
                     : "=r"(a0)
                     : "r"(a7));
    return a0;
}

int ecall_send(uint64_t ch, uint64_t msg)
{
    register uint64_t a7 __asm__("a7");
    register uint64_t a0 __asm__("a0");
    register uint64_t a1 __asm__("a1");
    a7 = 2;
    a0 = ch;
    a1 = msg;
    __asm__ volatile("ecall"
                     : "+r"(a0)
                     : "r"(a7), "r"(a1));
    return a0;
}

int ecall_recv(uint64_t ch, uint64_t* msg)
{
    register uint64_t a7 __asm__("a7");
    register uint64_t a0 __asm__("a0");
    register uint64_t a1 __asm__("a1");
    a7 = 3;
    a0 = ch;
    __asm__ volatile("ecall"
                     : "+r"(a0), "=r"(a1)
                     : "r"(a7));
    msg[0] = a1;
    return a0;
}

int ecall_write(uint64_t ch, uint64_t offset, uint64_t msg)
{
    register uint64_t a7 __asm__("a7");
    register uint64_t a0 __asm__("a0");
    register uint64_t a1 __asm__("a1");
    register uint64_t a2 __asm__("a2");
    a7 = 4;
    a0 = ch;
    a1 = offset;
    a2 = msg;
    __asm__ volatile("ecall"
                     : "+r"(a0)
                     : "r"(a7), "r"(a1));
    return a0;
}

int ecall_read(uint64_t ch, uint64_t offset, uint64_t* msg)
{
    register uint64_t a7 __asm__("a7");
    register uint64_t a0 __asm__("a0");
    register uint64_t a1 __asm__("a1");
    register uint64_t a2 __asm__("a2");
    a7 = 5;
    a0 = ch;
    a1 = offset;
    __asm__ volatile("ecall"
                     : "+r"(a0), "+r"(a1)
                     : "r"(a7));
    msg[0] = a1;
    return a0;
}
