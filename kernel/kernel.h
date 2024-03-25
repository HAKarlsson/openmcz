#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct channel {
	uint64_t *buf;
	uint64_t size, head, tail;
} channel_t;

typedef struct regs {
	uint64_t pc, ra, sp, gp, tp;
	uint64_t t0, t1, t2;
	uint64_t s0, s1;
	uint64_t a0, a1, a2, a3, a4, a5, a6, a7;
	uint64_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
	uint64_t t3, t4, t5, t6;
} regs_t;

typedef struct pmp {
	uint64_t cfg;
	uint64_t addr[8];
} pmp_t;

typedef struct zone {
	regs_t regs;
	pmp_t pmp;
	channel_t **chan_send;
	uint64_t n_chan_send;
	channel_t **chan_recv;
	uint64_t n_chan_recv;
} zone_t;

typedef struct sched {
	zone_t *zone;
	uint32_t ticks;
	int temporal_fence;
} sched_t;

volatile register zone_t *current __asm__("tp");

void kernel_init(void);
void kernel_yield(void);
