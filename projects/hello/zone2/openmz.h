#pragma once
#include <stdint.h>

static inline void ecall_yield(void) {
        register uint64_t t0 __asm__("t0");
        t0 = 0;
        __asm__ volatile ("ecall":: "r"(t0));
}
