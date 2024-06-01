#ifndef MTIME_H
#define MTIME_H
#include <stdint.h>

extern volatile uint64_t __mtime;
extern volatile uint64_t __mtimecmp;

static volatile uint64_t *mtime = &__mtime;
static volatile uint64_t *mtimecmp =  &__mtimecmp;

static inline uint64_t mtime_get(void)
{
	return mtime[0];
}

static inline void mtime_set(uint64_t val)
{
	mtime[0] = val;
}

static inline uint64_t mtimecmp_get(uint64_t hartid)
{
	return mtimecmp[hartid];
}

static inline void mtimecmp_set(uint64_t hartid, uint64_t val)
{
	mtimecmp[hartid] = val;
}

#endif /* MTIME_H */
