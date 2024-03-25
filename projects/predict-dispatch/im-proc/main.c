#include "../../image-processor/shared.h"
#include "api/openmz.h"
#include "api/util.h"
#include "comm.h"

volatile shared_t *const buf = (shared_t *)0x80000000;

extern char image[];

void setup()
{
}

void loop()
{
	grey(buf->greyed, image, 64, 64);
	resize(buf->resized, buf->greyed, 64, 64);
	sobel(buf->sobeled, buf->resized, 64, 32);
	ascii(buf->asciied, buf->sobeled, 62, 30);
	comm_puts("\n\n\n\n");
	comm_puts(buf->asciied);
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
	ecall_wfi();
}
