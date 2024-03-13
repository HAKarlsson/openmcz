#include "altc/altio.h"
#include "api/openmz.h"

volatile long *const shared_buffer = (long *)0x80008000;

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
        uint64_t start, end;
	ecall_wfi();

	start = read_cycle();
	for (int i = 0; i < 0x8000; i += 0x100)
		shared_buffer[i/sizeof(long)]++;
	end = read_cycle();

	alt_printf("%D\n", end - start);
}
