#include "kernel.h"
#include "macro.h"
#include "pmp.h"

#define N_HART 1

/****** ZONE CONFIGURATIONS ******/
static thread_t zoneA = {
        .regs = { 0x80004000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                	PMP_ADDR_NAPOT(0x80004000, 0x4000),
                	PMP_ADDR_NAPOT(0x03002000, 0x20),
                },
        },
	.queue_send = 0x1,
	.queue_recv = 0x0,
};

static thread_t zoneB = {
        .regs = { 0x80008000 },
        .pmp = {
                .cfg = 0x1b1f,
                .addr = {
                	PMP_ADDR_NAPOT(0x80008000, 0x4000),
                	PMP_ADDR_NAPOT(0x03002000, 0x20),
                },
        },
	.queue_send = 0x0,
	.queue_recv = 0x1,
};

/****** SCHEDULER CONFIGURATIONS ******/
const sched_t schedule[] = {
    {&zoneA, 100000, 0},
    {&zoneB, 100000, 0},
};

/* IPC configuration */
static uint64_t queue1_buf[8];

buffer_t buffers[] = {};
queue_t queues[] = {
	{
		.buf = queue1_buf,
		.size = 8,
	},
};

const uint64_t cspad = 10000;
