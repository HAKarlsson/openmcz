#include "api/openmz.h"
#include "../shared.h"

void setup()
{
}

void resize(char *out, const char *in, int xsize, int ysize)
{
	for (int j = 0; j < ysize; j += 2) {
		for (int i = 0; i < xsize; i++) {
			int c0 = in[i + j * xsize];
			int c1 = in[i + (j + 1) * xsize];
			*(out++) = (c0 + c1) / 2;
		}
	}
}

void loop()
{
        resize(shared->resized, shared->greyed, 64, 64);
	ecall_yield();
}
