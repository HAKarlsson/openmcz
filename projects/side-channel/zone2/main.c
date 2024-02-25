#include "altc/altio.h"
#include "api/openmz.h"

#include <stdint.h>

volatile uint64_t *const shared_buffer = (uint64_t *)0x80030000;

volatile char c;

static inline uint64_t read_cycle(void)
{
	uint64_t res;
	__asm__ volatile("csrr %0,cycle" : "=r"(res));
	return res;
}

void setup()
{
	alt_puts("setup spy");
}

void loop()
{
	ecall_wfi();
	uint64_t start = read_cycle();
	for (int i = 0; i < 128; ++i)
		shared_buffer[128 + i] = shared_buffer[i];
	uint64_t end = read_cycle();

	alt_printf("%D\n", (end - start) / 128);
}
