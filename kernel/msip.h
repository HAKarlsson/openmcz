#ifndef MSIP_H
#define MSIP_H
#include <stdint.h>

extern volatile int __msip;

static volatile int *msip = &__msip;

static inline int msip_get(uint64_t hartid)
{
	return msip[hartid];
}

static inline void msip_set(uint64_t hartid)
{
	msip[hartid] = 1;
}

static inline void msip_clear(uint64_t hartid)
{
	msip[hartid] = 0;
}

#endif /* MSIP_H */
