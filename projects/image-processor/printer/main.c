#include "api/openmz.h"
#include "altc/altio.h"
#include "../shared.h"

#include <stdint.h>

void setup()
{
}

void printer(const char *in, int xsize, int ysize)
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

void loop()
{
        printer(shared->asciied, 62, 30);
	ecall_yield();
}
