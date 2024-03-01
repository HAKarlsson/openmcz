#pragma once

#define MSTATUS_MIE 0x8

#define MIE_MTIE 0x80
#define MIP_MTIP 0x80

#define MCOUNTEREN_CY 0x1
#define MCOUNTEREN_TM 0x2
#define MCOUNTEREN_IR 0x4

#define SCOUNTEREN_CY 0x1
#define SCOUNTEREN_TM 0x2
#define SCOUNTEREN_IR 0x4

#ifndef __ASSEMBLER__
#include <stdint.h>

static inline void csrw_mstatus(uint64_t val)
{
	__asm__ volatile("csrw mstatus,%0" ::"r"(val));
}

static inline void csrw_mtvec(uint64_t val)
{
	__asm__ volatile("csrw mtvec,%0" ::"r"(val));
}

static inline void csrw_mie(uint64_t val)
{
	__asm__ volatile("csrw mie,%0" ::"r"(val));
}

static inline void csrw_spad(uint64_t val)
{
	__asm__ volatile("csrw 0x702,%0" ::"r"(val));
}

static inline void csrw_mcounteren(uint64_t val)
{
	__asm__ volatile("csrw mcounteren,%0" ::"r"(val));
}

static inline void csrw_scounteren(uint64_t val)
{
	__asm__ volatile("csrw scounteren,%0" ::"r"(val));
}

static inline void csrw_pmpcfg0(uint64_t val)
{
	__asm__ volatile("csrw pmpcfg0,%0" ::"r"(val));
}

static inline void csrw_pmpaddr0(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr0,%0" ::"r"(val));
}

static inline void csrw_pmpaddr1(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr1,%0" ::"r"(val));
}

static inline void csrw_pmpaddr2(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr2,%0" ::"r"(val));
}

static inline void csrw_pmpaddr3(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr3,%0" ::"r"(val));
}

static inline void csrw_pmpaddr4(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr4,%0" ::"r"(val));
}

static inline void csrw_pmpaddr5(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr5,%0" ::"r"(val));
}

static inline void csrw_pmpaddr6(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr6,%0" ::"r"(val));
}

static inline void csrw_pmpaddr7(uint64_t val)
{
	__asm__ volatile("csrw pmpaddr7,%0" ::"r"(val));
}

static inline uint64_t csrr_mie(void)
{
	uint64_t val;
	__asm__ volatile("csrr %0,mie" : "=r"(val));
	return val;
}

static inline uint64_t csrr_mip(void)
{
	uint64_t val;
	__asm__ volatile("csrr %0,mip" : "=r"(val));
	return val;
}
#endif
