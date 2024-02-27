#include "kernel.h"
#include "macro.h"

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

/****** ZONE CONFIGURATIONS ******/
static zone_t grey = {
        .regs = { 0x80004000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x80004000, 0x4000),
                PMP_NAPOT(0x80020000, 0x1000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t resize = {
        .regs = { 0x80008000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x80008000, 0x4000),
                PMP_NAPOT(0x80020000, 0x1000),
                PMP_NAPOT(0x80021000, 0x1000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t sobel = {
        .regs = { 0x8000C000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x8000C000, 0x4000),
                PMP_NAPOT(0x80021000, 0x1000),
                PMP_NAPOT(0x80022000, 0x1000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t ascii = {
        .regs = { 0x80010000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x80010000, 0x4000),
                PMP_NAPOT(0x80022000, 0x1000),
                PMP_NAPOT(0x80023000, 0x1000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t printer = {
        .regs = { 0x80014000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x80014000, 0x4000),
                PMP_NAPOT(0x80023000, 0x1000),
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
	{ &grey,    500000000, 0},
	{ &resize,  500000000, 0},
	{ &sobel,   500000000, 0},
	{ &ascii,   500000000, 0},
	{ &printer, 500000000, 0},
};

const uint64_t yield_buffer = 10;
