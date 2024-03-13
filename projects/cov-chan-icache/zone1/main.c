#include "altc/altio.h"
#include "api/openmz.h"

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

unsigned int lfsr113_Bits (void)
{
        static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
        unsigned int b;
        b  = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18) ^ b;
        b  = ((z2 << 2) ^ z2) >> 27; 
        z2 = ((z2 & 4294967288U) << 2) ^ b;
        b  = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7) ^ b;
        b  = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13) ^ b;
        return (z1 ^ z2 ^ z3 ^ z4);
}

void loop()
{
	uint64_t data[2];
        int rand = lfsr113_Bits();
        alt_printf("%d,", rand & 1);
        if (rand & 4) {
	        ecall_send(0, data);
	        ecall_recv(0, data);
        }
	wait();
}
