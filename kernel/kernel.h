#ifndef KERNEL_H
#define KERNEL_H

#ifndef HART_COUNT
#define HART_COUNT 1
#endif /* HART_COUNT */

#include <stddef.h>
#include <stdint.h>

typedef struct queue {
	uint64_t size; 
	uint64_t head;
	uint64_t tail;
	uint64_t *volatile buf;
} queue_t;

typedef struct buffer {
	uint64_t size;
	uint64_t *buf;
} buffer_t;

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

typedef struct thread {
	regs_t regs;
	pmp_t pmp;
	uint64_t queue_send;
	uint64_t queue_recv;
	uint64_t buffer_write;
	uint64_t buffer_read;
} thread_t;

typedef struct sched {
	thread_t *threads;
	uint64_t ticks;
	int temporal_fence;
} sched_t;

void kernel_init(void);
thread_t *kernel_sched(void);

extern queue_t queues[];
extern buffer_t buffers[];
extern sched_t sched[];

#endif /* KERNEL_H */
