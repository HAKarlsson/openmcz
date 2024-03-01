#pragma once

static inline void fence_t(void)
{
	__asm__ volatile(".word 0x0B");
}
