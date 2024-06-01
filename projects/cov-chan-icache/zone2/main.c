#include "altio.h"
#include "openmcz.h"

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
	uint64_t data[2];

        // Flush instruction cache
	__asm__ volatile("fence.i");

        // Yield
	ecall_wfi();

	uint64_t start = read_cycle();
	ecall_send(0, data);
	ecall_recv(0, data);
	uint64_t end = read_cycle();

	alt_printf("%D\n", (end - start));
}
