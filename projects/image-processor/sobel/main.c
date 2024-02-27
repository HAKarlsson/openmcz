#include "../shared.h"
#include "api/openmz.h"

void setup()
{
}

static int sqrt(int s)
{
	// Zero yields zero
	// One yields one
	if (s <= 1)
		return s;

	// Initial estimate (must be too high)
	unsigned int x0 = s / 2;

	// Update
	unsigned int x1 = (x0 + s / x0) / 2;

	while (x1 < x0) // Bound check
	{
		x0 = x1;
		x1 = (x0 + s / x0) / 2;
	}
	return x0;
}

static void sobel(char *out, const char *in, int xsize, int ysize)
{
	for (int y = 1; y < ysize - 1; y++) {
		for (int x = 1; x < xsize - 1; x++) {
			int p00 = in[x - 1 + (y - 1) * xsize];
			int p10 = in[x + (y - 1) * xsize];
			int p20 = in[x + 1 + (y - 1) * xsize];

			int p01 = in[x - 1 + y * xsize];
			int p11 = in[x + y * xsize];
			int p21 = in[x + 1 + y * xsize];

			int p02 = in[x - 1 + (y + 1) * xsize];
			int p12 = in[x + (y + 1) * xsize];
			int p22 = in[x + 1 + (y + 1) * xsize];

			int dx = (p00 + 2 * p01 + p02) - (p20 + 2 * p21 + p22);
			int dy = (p00 + 2 * p10 + p20) - (p02 + 2 * p12 + p22);
			int dxy = sqrt(dx * dx + dy * dy) / 4;
			if (dxy > 255)
				*(out++) = 255;
			else
				*(out++) = dxy;
		}
	}
}

void loop()
{
	sobel(shared->sobeled, shared->resized, 64, 32);
	ecall_yield();
}
