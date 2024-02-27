#include "api/openmz.h"
#include "../shared.h"

#include <stdint.h>

static const char ascii_map[] = { ' ', '.', ':', '-', '=', '+', '/', 't',
			'z', 'U', 'w', '*', '0', '#', '%', '@' };

void setup()
{
}

void ascii(char *out, const char *in, int xsize, int ysize)
{
	for (int i = 0; i < xsize * ysize; ++i) {
		out[i] = ascii_map[in[i] / 16];
	}
}

void loop()
{
        ascii(shared->asciied, shared->sobeled, 62, 30);
	ecall_yield();
}
