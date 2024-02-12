#pragma once

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define csrw(csr, val) \
        __asm__ volatile ("csrw " #csr",%0" :: "r"(val))

#define csrr(csr) ({ \
                uint64_t __val; \
                __asm__ volatile ("csrr %0," #csr : "=r"(__val)); \
                __val; \
                })

#define temporal_fence() __asm__ volatile (".word 0x0000000B");

#define wfi() \
        __asm__ volatile ("wfi");

#define PMP_NAPOT(base, size) \
        (((base) | ((size) / 2 - 1)) >> 2)
