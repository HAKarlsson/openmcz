#include "time.h"

static volatile uint64_t *time = (uint64_t *)0x200bff8;
static volatile uint64_t *timeout = (uint64_t *)0x2004000;

uint64_t time_get(void)
{
	return *time;
}

void time_set(uint64_t val)
{
	*time = val;
}

void timeout_set(uint64_t val)
{
	*timeout = val;
}

uint64_t timeout_get(void)
{
	return *timeout;
}
