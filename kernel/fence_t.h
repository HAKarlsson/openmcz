#ifndef FENCE_T_H
#define FENCE_T_H

#ifdef ENABLE_TEMPORAL_FENCE
static inline void fence_t(void)
{
	__asm__ volatile(".word 0x0B");
}
#else
static inline void fence_t(void)
{
}
#endif

#endif /* FENCE_T_H */
