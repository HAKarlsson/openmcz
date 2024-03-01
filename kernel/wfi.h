#pragma once

static inline void wfi(void)
{
	__asm__ volatile("wfi");
}
