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
	uint64_t data[2];
	ecall_wfi();
	__asm__ volatile("fence.i");

	uint64_t start = read_cycle();
	ecall_send(0, data);
	ecall_recv(0, data);
	uint64_t end = read_cycle();

	uint64_t t = end - start;
	avg = (avg == 0) ? t : ((avg * 15 + t) / 16);

	alt_printf("%c %D\n", (t > avg) ? 'T' : 'F', (end - start));
}
