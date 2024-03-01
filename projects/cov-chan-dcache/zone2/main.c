#include "altc/altio.h"
#include "api/openmz.h"

volatile char *const shared_buffer = (char *)0x80030000;

static inline uint64_t read_cycle(void)
{
	uint64_t res;
	__asm__ volatile("csrr %0,cycle" : "=r"(res));
	return res;
}

void setup()
{
}

void loop()
{
	static uint64_t avg = 0;
	ecall_wfi();
	uint64_t start = read_cycle();
	for (int i = 0; i < 0x10000; i += 0x10)
		shared_buffer[i]++;
	uint64_t end = read_cycle();

	uint64_t t = end - start;
	avg = (avg * 15 + t) / 16;

	alt_printf("%d %D\n", (t > avg), (end - start));
}
