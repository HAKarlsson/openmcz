#pragma once

#define MIE_MTIE 0x80
#define MIP_MTIP 0x80

#define MCOUNTEREN_CY 0x1
#define MCOUNTEREN_TM 0x2
#define MCOUNTEREN_IR 0x4

#define SCOUNTEREN_CY 0x1
#define SCOUNTEREN_TM 0x2
#define SCOUNTEREN_IR 0x4

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define csrw(csr, val) __asm__ volatile("csrw " #csr ",%0" ::"r"(val))

#define csrr(csr)                                                \
	({                                                       \
		uint64_t __val;                                  \
		__asm__ volatile("csrr %0," #csr : "=r"(__val)); \
		__val;                                           \
	})

#define temporal_fence() __asm__ volatile(".word 0x0B")

#define mip() (csrr(mip) & csrr(mie))

#define wfi() __asm__ volatile("wfi")

#define PMP_NAPOT(base, size) (((base) | ((size) / 2 - 1)) >> 2)
