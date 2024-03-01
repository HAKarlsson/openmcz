#include "altc/altio.h"
#include "api/openmz.h"
#include "api/util.h"

volatile char *const shared_buffer = (char *)0x80020000;

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
	wait();
	wait();
	for (int i = 0; i < 0x10000; i += 0x10)
		shared_buffer[i]++;
}
