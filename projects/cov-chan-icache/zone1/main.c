#include "altc/altio.h"
#include "api/openmz.h"

volatile char *const shared_buffer = (char *)0x80020000;

static inline uint64_t read_cycle(void)
{
	uint64_t res;
	__asm__ volatile("csrr %0,cycle" : "=r"(res));
	return res;
}

void setup()
{
}

void wait()
{
	uint64_t last_cycle = read_cycle();
	uint64_t curr_cycle = read_cycle();
	while ((curr_cycle - last_cycle) < 1000) {
		last_cycle = curr_cycle;
		curr_cycle = read_cycle();
	}
}

void loop()
{
	uint64_t data[2];
	wait();
	wait();
	ecall_send(0, data);
	ecall_recv(0, data);
}
