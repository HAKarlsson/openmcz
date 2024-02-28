#include "../shared.h"

#include <stdint.h>

extern char const image[];

static inline uint64_t read_cycle(void)
{
	uint64_t res;
	__asm__ volatile("csrr %0,mcycle" : "=r"(res));
	return res;
}

void setup()
{
}

void loop()
{
        uint64_t start = read_cycle();
        grey(shared->greyed, image, 64, 64);
        resize(shared->resized, shared->greyed, 64, 64);
        sobel(shared->sobeled, shared->resized, 64, 32);
        ascii(shared->asciied, shared->sobeled, 62, 30);
        uint64_t end = read_cycle();
        alt_printf("cycles: %D\n", end - start);
        //alt_puts(shared->asciied);
}
