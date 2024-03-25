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

static uint64_t chan_buf1[256];
static channel_t chan1 = {
	.buf = chan_buf1,
	.size = ARRAY_SIZE(chan_buf1),
	.head = 0,
	.tail = 0,
};

static uint64_t chan_buf2[2];
static channel_t chan2 = {
	.buf = chan_buf2,
	.size = ARRAY_SIZE(chan_buf2),
	.head = 0,
	.tail = 0,
};

static channel_t *channels[] = { &chan1, &chan2 };

/****** ZONE CONFIGURATIONS ******/
static zone_t im_proc = {
        .regs = { 0x80008000 },
        .pmp = {
                .cfg = 0x1f,
                .addr = {
                PMP_NAPOT(0x80008000, 0x8000),
                },
        },
        .chan_send = channels,
        .n_chan_send = ARRAY_SIZE(channels),
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t uart = {
        .regs = { 0x10002000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                PMP_NAPOT(0x10002000, 0x2000),
                PMP_NAPOT(0x03002000, 0x20),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = channels,
        .n_chan_recv = ARRAY_SIZE(channels),
};

static zone_t trasher = {
        .regs = { 0x10004000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                PMP_NAPOT(0x10004000, 0x2000),
                PMP_NAPOT(0x80010000, 0x10000),
                },
        },
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
	{ &im_proc,  10000, FALSE},
	{ &uart,  100000000, FALSE},
	{ &trasher,  1000000, FALSE},
};

const uint64_t yield_buffer = 8;
const uint64_t cspad = 750;
