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
static thread_t im_proc = {
    .regs = { 0x80008000 },
    .pmp = {
        .cfg = 0x1f,
        .addr = {
            PMP_ADDR_NAPOT(0x80008000, 0x8000),
        },
    },
};

static thread_t uart = {
    .regs = { 0x10002000 },
    .pmp = {
        .cfg = 0x1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10002000, 0x2000),
            PMP_ADDR_NAPOT(0x03002000, 0x20),
        },
    },
};

static thread_t trasher = {
    .regs = { 0x10004000 },
    .pmp = {
        .cfg = 0x1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10004000, 0x2000),
            PMP_ADDR_NAPOT(0x80010000, 0x10000),
        },
    },
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
    { &uart, 100000, TRUE },
    { &trasher, 800000, FALSE },
    { &im_proc, 100000, TRUE },
};

buffer_t buffers[] = {};
queue_t queues[] = {};

const uint64_t yield_buffer = 8;
const uint64_t cspad = 750;
