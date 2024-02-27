#include "api/openmz.h"
#include "api/util.h"
#include "../shared.h"

#include <stdint.h>

extern char const image[];
uint64_t *time = (uint64_t *)(0x80070000 - 8);

void setup()
{
}

static inline void grey(char *restrict out, const char *in, int xsize, int ysize)
{

        for (int i = 0; i < xsize * ysize * 3; i += 3) {
                int red = in[i];
                int green = in[i + 1];
                int blue = in[i + 2];
	        *(out++) = (red * 9 + green * 5 + blue * 2) / 16;
        }
}

void loop()
{
	//*time = read_cycle();
        grey(shared->greyed, image, 64, 64);
	ecall_yield();
}
