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
 * } thread_t;
 *
 * typedef struct sched {
 *         thread_t *zone;
 *         uint64_t ticks;
 * } sched_t;
 */

/****** ZONE CONFIGURATIONS ******/
static thread_t im_proc = {
    .regs = { 0x10008000 },
    .pmp = {
        .cfg = 0x1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10008000, 0x8000),
            PMP_ADDR_NAPOT(0x80000000, 0x8000),
        },
    },
    .queue_send = 1
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
    .queue_recv = 1
};

static thread_t measurer = {
    .regs = { 0x10004000 },
    .pmp = {
        .cfg = 0x1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10004000, 0x2000),
            PMP_ADDR_NAPOT(0x03002000, 0x20),
        },
    },
};

static thread_t trasher = {
    .regs = { 0x10006000 },
    .pmp = {
        .cfg = 0x1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10006000, 0x2000),
            PMP_ADDR_NAPOT(0x80008000, 0x8000),
        },
    },
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
    { &trasher, 250000, FALSE },
    { &im_proc, 250000, FALSE },
    { &uart, 250000, FALSE },
    { &measurer, 250000, TRUE /* fence.t? */ },
};

static uint64_t chan_buf1[256];

buffer_t buffers[] = {};

queue_t queues[] = {};
const uint64_t yield_buffer = 8;
const uint64_t cspad = 500;
