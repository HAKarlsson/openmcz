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
static thread_t grey = {
    .regs = { 0x10008000 },
    .pmp = {
        .cfg = 0x1b1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10008000, 0x4000),
            PMP_ADDR_NAPOT(0x80000000, 0x1000),
            PMP_ADDR_NAPOT(0x80004000, 0x8),
        },
    },
};

static thread_t resize = {
    .regs = { 0x10002000 },
    .pmp = {
        .cfg = 0x1b1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10002000, 0x2000),
            PMP_ADDR_NAPOT(0x80000000, 0x1000),
            PMP_ADDR_NAPOT(0x80001000, 0x1000),
        },
    },
};

static thread_t sobel = {
    .regs = { 0x10004000 },
    .pmp = {
        .cfg = 0x1b1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10004000, 0x2000),
            PMP_ADDR_NAPOT(0x80001000, 0x1000),
            PMP_ADDR_NAPOT(0x80002000, 0x1000),
        },
    },
};

static thread_t ascii = {
    .regs = { 0x10006000 },
    .pmp = {
        .cfg = 0x1b1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x10006000, 0x2000),
            PMP_ADDR_NAPOT(0x80002000, 0x1000),
            PMP_ADDR_NAPOT(0x80003000, 0x1000),
        },
    },
};

static thread_t uart = {
    .regs = { 0x1000C000 },
    .pmp = {
        .cfg = 0x1b1b1b1f,
        .addr = {
            PMP_ADDR_NAPOT(0x1000C000, 0x2000),
            PMP_ADDR_NAPOT(0x80003000, 0x1000),
            PMP_ADDR_NAPOT(0x80004000, 0x8),
            PMP_ADDR_NAPOT(0x03002000, 0x20),
        },
    },
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
    { &grey, 500000000, TRUE },
    { &resize, 500000000, TRUE },
    { &sobel, 500000000, TRUE },
    { &ascii, 500000000, TRUE },
    { &uart, 500000000, TRUE },
};

buffer_t buffers[] = {};
queue_t queues[] = {};

const uint64_t yield_buffer = 8;
const uint64_t cspad = 0;
