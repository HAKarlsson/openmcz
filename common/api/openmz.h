#pragma once
#include <stdint.h>

static inline void ecall_yield(void)
{
	register uint64_t t0 __asm__("t0");
	t0 = 0;
	__asm__ volatile("ecall" ::"r"(t0));
}

static inline void ecall_wfi(void)
{
	register uint64_t t0 __asm__("t0");
	t0 = 1;
	__asm__ volatile("ecall" ::"r"(t0));
}

static inline int ecall_send(uint64_t ch, uint64_t msg[2])
{
	register uint64_t t0 __asm__("t0");
	register uint64_t a0 __asm__("a0");
	register uint64_t a1 __asm__("a1");
	register uint64_t a2 __asm__("a2");
	t0 = 2;
	a0 = ch;
	a1 = msg[0];
	a2 = msg[1];
	__asm__ volatile("ecall" : "+r"(a0) : "r"(t0), "r"(a1), "r"(a2));
        return a0;
}

static inline int ecall_recv(uint64_t ch, uint64_t msg[2])
{
	register uint64_t t0 __asm__("t0");
	register uint64_t a0 __asm__("a0");
	register uint64_t a1 __asm__("a1");
	register uint64_t a2 __asm__("a2");
	t0 = 3;
	a0 = ch;
	__asm__ volatile("ecall" : "+r"(a0), "+r"(a1), "+r"(a2) : "r"(t0));
	msg[0] = a1;
	msg[1] = a2;
        return a0;
}
