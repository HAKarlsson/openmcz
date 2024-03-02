#include "../../image-processor/shared.h"
#include "api/openmz.h"
#include "api/util.h"
#include "comm.h"

#define BUFFER_SIZE 0x1000

extern char image[];

char buffer[2][BUFFER_SIZE];

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
	grey(buffer[0], image, 64, 64);
	resize(buffer[0], buffer[0], 64, 64);
	sobel(buffer[1], buffer[0], 64, 32);
	ascii(buffer[0], buffer[1], 62, 30);
	comm_puts("\n\n\n\n");
	comm_puts(buffer[0]);
	for (int i = 0; i < 12; ++i)
		wait();
}
