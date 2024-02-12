#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct channel channel_t;
typedef struct zone zone_t;
typedef struct sched sched_t;

struct channel {
        uint64_t *buf;
        uint64_t size, head, tail;
};

struct zone {
        uint64_t regs[32];
        uint64_t pmpcfg;
        uint64_t pmpaddr[8];
        channel_t **chan_send; 
        uint64_t n_chan_send;
        channel_t **chan_recv;
        uint64_t n_chan_recv;
};

struct sched {
        zone_t *zone;
        uint64_t ticks;
};

register zone_t *current __asm__("tp");

void kernel_init(void);
void kernel_yield(void);
void kernel_sched(void);
