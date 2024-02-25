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
static zone_t zone1 = {
        .regs = { 0x80010000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x80010000, 0x10000),
                PMP_NAPOT(0x10000000, 0x20),
                PMP_NAPOT(0x80030000, 0x10000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t zone2 = {
        .regs = { 0x80020000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x80020000, 0x10000),
                PMP_NAPOT(0x10000000, 0x20),
                PMP_NAPOT(0x80030000, 0x10000),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
	{&zone1,  500000, 1},
	{ &zone2, 500000, 1},
};

const uint64_t yield_buffer = 10;
