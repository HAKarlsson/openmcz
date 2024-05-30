#include "altc/altio.h"
#include "api/openmz.h"

volatile long *const buffer = (long *)0x80008000;


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
	static long avg = 0;
        uint64_t start, elapsed;

	// Measure access to buffer
	start = read_cycle();
	for (int i = 0; i < 0x8000; i += 0x100)
		buffer[i/sizeof(long)]++;
	for (int i = 0; i < 0x8000; i += 0x100)
		buffer[i/sizeof(long)]++;
	elapsed = read_cycle() - start;

	alt_printf("Spy: Buffer access time is %D cycles.\n", elapsed);

	if (avg == 0) avg = elapsed;

	// Moving average
	avg = (9 * avg + elapsed)/ 10;

	alt_printf("Spy: Average access time is %D cycles.\n", avg);
	alt_printf("Spy: I guess %d.\n",  (elapsed > avg));
	
	ecall_wfi();
}
