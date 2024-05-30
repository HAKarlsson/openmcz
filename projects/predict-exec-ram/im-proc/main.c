#include "../../image-processor/shared.h"
#include "api/openmz.h"
#include "api/util.h"
#include "comm.h"
#include "altc/altio.h"

char buf[4][4096];

extern char image[];

void setup()
{
}

void loop()
{
        uint64_t data[2];
        data[0] = read_cycle();
	grey(&buf[0], image, 64, 64);
	resize(&buf[1], &buf[0], 64, 64);
	sobel(&buf[2], &buf[1], 64, 32);
	ascii(&buf[3], &buf[2], 62, 30);
        comm_puts(&buf[3]);
        data[1] = read_cycle();
        ecall_send(1, data);
	ecall_yield();
}
