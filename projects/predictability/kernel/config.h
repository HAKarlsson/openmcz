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
static uint64_t chan_buf1[256];
static channel_t chan1 = {
	.buf = chan_buf1,
	.size = ARRAY_SIZE(chan_buf1),
	.head = 0,
	.tail = 0,
};

static channel_t *channels[] = { &chan1 };

/****** ZONE CONFIGURATIONS ******/
static zone_t zone1 = {
        .regs = { 0x80010000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                PMP_NAPOT(0x80010000, 0x8000),
                },
        },
        .chan_send = channels,
        .n_chan_send = ARRAY_SIZE(channels),
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t zone2 = {
        .regs = { 0x80004000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                PMP_NAPOT(0x80004000, 0x4000),
                PMP_NAPOT(0x10000000, 0x20),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = channels,
        .n_chan_recv = ARRAY_SIZE(channels),
};

static zone_t zone3 = {
        .regs = { 0x80008000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                PMP_NAPOT(0x80008000, 0x4000),
                PMP_NAPOT(0x10000000, 0x20),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
	{&zone1,  100000, TRUE },
	{ &zone2, 800000, FALSE},
	{ &zone3, 100000, TRUE },
};

const uint64_t yield_buffer = 16;
// const uint64_t spad = 4000;
const uint64_t spad = 0;
