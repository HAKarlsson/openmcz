#include "kernel.h"
#include "macro.h"
#include "pmp.h"

/**
 *
 * typedef struct channel {
 *         uint64_t *buf;
 *         uint64_t size, head, tail;
 * } channel_t;
 *
 * typedef struct zone {
 *         uint64_t regs[32];
 *         uint64_t pmpcfg;
 *         uint64_t pmpaddr[8];
 *         channel_t *chan_send;
 *         uint64_t n_chan_send;
 *         channel_t *chan_recv;
 *         uint64_t n_chan_recv;
 * } zone_t;
 *
 * typedef struct sched {
 *         zone_t *zone;
 *         uint64_t ticks;
 * } sched_t;
 */

#define N_HARTS 2

/****** ZONE CONFIGURATIONS ******/
static thread_t zoneA[N_HARTS] = {
	[0] = {       .regs = { 0x10008000 },
		.pmp = {
			.cfg = 0x1b1f,
			.addr = {
				PMP_NAPOT(0x10008000, 0x4000),
				PMP_NAPOT(0x03002000, 0x20),
			},
		},
		.queue_send = 0x0,
		.queue_recv = 0x1,
	},
	[1] = {
	}
};

static thread_t zoneB[N_HARTS] = {
	[0] = {	},
	[1] = {
		.regs = { 0x10004000 },
		.pmp = {
			.cfg = 0x1b1f,
			.addr = {
				PMP_NAPOT(0x10004000, 0x4000),
				PMP_NAPOT(0x03002000, 0x20),
			},
		},
		.queue_send = 0x1,
		.queue_recv = 0x0,
	}
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
	{zoneA, 100000, 1},
	{zoneB, 100000, 1},
};

/* IPC configuration */
static uint64_t queue1_buf[100];

buffer_t buffers[0];
queue_t queues[] = {
	{
		.buf = queue1_buf,
		.size = 100,
	},
};

const uint64_t cspad = 10000;
