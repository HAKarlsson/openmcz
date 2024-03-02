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

/****** IPC CONFIGURATIONS ******/

static uint64_t chan_buf1[32];
static channel_t chan1 = {
	.buf = chan_buf1,
	.size = ARRAY_SIZE(chan_buf1),
	.head = 0,
	.tail = 0,
};

static uint64_t chan_buf2[32];
static channel_t chan2 = {
	.buf = chan_buf2,
	.size = ARRAY_SIZE(chan_buf2),
	.head = 0,
	.tail = 0,
};

/****** ZONE CONFIGURATIONS ******/
static channel_t *zone1_send_chan[] = { &chan1 };
static channel_t *zone1_recv_chan[] = { &chan2 };
static zone_t zone1 = {
        .regs = { 0x80004000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                PMP_NAPOT(0x80004000, 0x4000),
                PMP_NAPOT(0x10000000, 0x20),
                },
        },
        .chan_send = zone1_send_chan,
        .n_chan_send = ARRAY_SIZE(zone1_send_chan),
        .chan_recv = zone1_recv_chan,
        .n_chan_recv = ARRAY_SIZE(zone1_recv_chan),
};

static channel_t *zone2_send_chan[] = { &chan2 };
static channel_t *zone2_recv_chan[] = { &chan1 };
static zone_t zone2 = {
        .regs = { 0x80008000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                PMP_NAPOT(0x80008000, 0x4000),
                PMP_NAPOT(0x10000000, 0x20),
                },
        },
        .chan_send = zone2_send_chan,
        .n_chan_send = ARRAY_SIZE(zone2_send_chan),
        .chan_recv = zone2_recv_chan,
        .n_chan_recv = ARRAY_SIZE(zone2_recv_chan),
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
	{&zone1,  100000, 1},
	{ &zone2, 100000, 1},
};

const uint64_t yield_buffer = 16;
const uint64_t spad = 4000;
