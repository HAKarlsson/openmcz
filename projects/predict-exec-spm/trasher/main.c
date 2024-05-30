#include "altc/altio.h"
#include "api/openmz.h"
#include "api/util.h"

#include <stdint.h>

volatile uint64_t *const buffer = (uint64_t *)0x80010000;

void setup()
{
}

unsigned int lfsr113_Bits(void)
{
	static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
	unsigned int b;
	b = ((z1 << 6) ^ z1) >> 13;
	z1 = ((z1 & 4294967294U) << 18) ^ b;
	b = ((z2 << 2) ^ z2) >> 27;
	z2 = ((z2 & 4294967288U) << 2) ^ b;
	b = ((z3 << 13) ^ z3) >> 21;
	z3 = ((z3 & 4294967280U) << 7) ^ b;
	b = ((z4 << 3) ^ z4) >> 12;
	z4 = ((z4 & 4294967168U) << 13) ^ b;
	return (z1 ^ z2 ^ z3 ^ z4);
}

void loop()
{
	unsigned int v = lfsr113_Bits();

	// Randomly fence.i
	if (v & 1) {
		asm volatile("fence.i");
	}

	v >>= 1;

	// Select random number of lines to evict
	int n = v % 0x2000;

	// Randomly evict lines.
	for (int i = 0; i < n; i++) {
		int loc = lfsr113_Bits() % 0x10000;
		buffer[loc / 8]++;
	}
	ecall_yield();
}
