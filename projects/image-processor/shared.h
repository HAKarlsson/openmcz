#pragma once

#include <stdint.h>

static const char ascii_map[] = { ' ', '.', ':', '-', '=', '+', '/', 't',
			'z', 'U', 'w', '*', '0', '#', '%', '@' };

#define BUFF_SIZE 0x1000
typedef struct shared {
        char greyed[BUFF_SIZE];
        char resized[BUFF_SIZE];
        char sobeled[BUFF_SIZE];
        char asciied[BUFF_SIZE];
        uint64_t time;
} shared_t;

static shared_t * const shared = (shared_t*)0x80020000;

static inline void grey(char *restrict out, const char *in, int xsize, int ysize)
{

        for (int i = 0; i < xsize * ysize * 3; i += 3) {
                int red = in[i];
                int green = in[i + 1];
                int blue = in[i + 2];
	        *(out++) = (red * 9 + green * 5 + blue * 2) / 16;
        }
}

static void resize(char *out, const char *in, int xsize, int ysize)
{
	for (int j = 0; j < ysize; j += 2) {
		for (int i = 0; i < xsize; i++) {
			int c0 = in[i + j * xsize];
			int c1 = in[i + (j + 1) * xsize];
			*(out++) = (c0 + c1) / 2;
		}
	}
}

static int isqrt(int s)
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
			int dxy = isqrt(dx * dx + dy * dy) / 4;
			if (dxy > 255)
				*(out++) = 255;
			else
				*(out++) = dxy;
		}
	}
}
static void ascii(char *out, const char *in, int xsize, int ysize)
{
	for (int i = 0; i < xsize * ysize; ++i) {
		out[i] = ascii_map[in[i] / 16];
	}
}

static void printer(const char *in, int xsize, int ysize)
{
        char buf[128];
	for (int y = 0; y < ysize; ++y) {
                for (int x = 0; x < xsize; ++x) {
                        buf[x] = *(in++);
                }
                buf[xsize] = '\0';
                alt_puts(buf);
        }
        alt_puts("");
}
