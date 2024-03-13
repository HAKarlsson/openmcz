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

/****** ZONE CONFIGURATIONS ******/
static zone_t zone1 = {
        .regs = { 0x10004000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x10004000, 0x4000),
                PMP_NAPOT(0x80000000, 0x8000),
                PMP_NAPOT(0x03002000, 0x20),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

static zone_t zone2 = {
        .regs = { 0x10008000 },
        .pmp = {
                .cfg = 0x1b1b1f,
                .addr = {
                PMP_NAPOT(0x10008000, 0x4000),
                PMP_NAPOT(0x80008000, 0x8000),
                PMP_NAPOT(0x03002000, 0x20),
                },
        },
        .chan_send = NULL,
        .n_chan_send = 0,
        .chan_recv = NULL,
        .n_chan_recv = 0,
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
	{ &zone1, 2000, TRUE, &zone1 },
	{ &zone2, 2000, TRUE, &zone2 },
};

const uint64_t yield_buffer = 8;
const uint64_t cspad = 22000;
