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
static uint64_t chan_buf1[2];
static channel_t chan1 = {
	.buf = chan_buf1,
	.size = ARRAY_SIZE(chan_buf1),
	.head = 0,
	.tail = 0,
};

channel_t *channels[] = { &chan1 };

/****** ZONE CONFIGURATIONS ******/
static zone_t grey = {
        .regs = { 0x10008000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x10008000, 0x4000),
                PMP_NAPOT(0x80000000, 0x1000),
                PMP_NAPOT(0x80004000, 0x8),
                },
        },
        .chan_send = channels,
        .n_chan_send = ARRAY_SIZE(channels),
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t resize = {
        .regs = { 0x10002000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x10002000, 0x2000),
                PMP_NAPOT(0x80000000, 0x1000),
                PMP_NAPOT(0x80001000, 0x1000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t sobel = {
        .regs = { 0x10004000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x10004000, 0x2000),
                PMP_NAPOT(0x80001000, 0x1000),
                PMP_NAPOT(0x80002000, 0x1000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t ascii = {
        .regs = { 0x10006000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x10006000, 0x2000),
                PMP_NAPOT(0x80002000, 0x1000),
                PMP_NAPOT(0x80003000, 0x1000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t uart = {
        .regs = { 0x1000C000 },
        .pmp = {
                .cfg = 0x1b1b1b1f,
                .addr = {
                PMP_NAPOT(0x1000C000, 0x2000),
                PMP_NAPOT(0x80003000, 0x1000),
                PMP_NAPOT(0x80004000, 0x8),
                PMP_NAPOT(0x03002000, 0x20),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = channels,
        .n_chan_recv = ARRAY_SIZE(channels),
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
	{&grey,    500000000, FALSE, NULL},
	{ &resize, 500000000, FALSE, NULL},
	{ &sobel,  500000000, FALSE, NULL},
	{ &ascii,  500000000, FALSE, NULL},
	{ &uart,   500000000, FALSE, NULL},
};

const uint64_t yield_buffer = 8;
const uint64_t cspad = 0;
