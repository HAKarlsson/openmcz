#include "altc/altio.h"
#include "api/openmz.h"

volatile uint64_t *const shared_buffer = (uint64_t *)0x80030000;

static inline uint64_t read_cycle(void)
{
	uint64_t res;
	__asm__ volatile("csrr %0,cycle" : "=r"(res));
	return res;
}

void setup()
{
	alt_puts("setup trojan");
}

void loop()
{
	static int t = 0;
	ecall_wfi();
	if (t++ % 2 == 0)
		for (int i = 0; i < 128; ++i)
			shared_buffer[i] += 0xdeadbeef;
}
