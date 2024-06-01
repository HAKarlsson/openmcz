#ifndef CSR_H
#define CSR_H

#include <stdint.h>

#define MIE_MTIE 0x80
#define MIP_MTIP 0x80
#define MIE_MSIE 0x08
#define MIP_MSIP 0x08

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

static inline void csrs_mie(uint64_t val)
{
	__asm__ volatile("csrs mie,%0" ::"r"(val));
}

static inline void csrc_mie(uint64_t val)
{
	__asm__ volatile("csrc mie,%0" ::"r"(val));
}

static inline void csrw_cspad(uint64_t val)
{
	__asm__ volatile("csrw 0x7C3,%0" ::"r"(val));
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

static inline uint64_t csrr_mcause(void)
{
	uint64_t val;
	__asm__ volatile("csrr %0,mcause" : "=r"(val));
	return val;
}

static inline uint64_t csrr_mhartid(void)
{
	uint64_t val;
	__asm__ volatile("csrr %0,mhartid" : "=r"(val));
	return val;
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
#endif /* CSR_H */
