#include "altc/altio.h"
#include "api/openmz.h"
#include "api/util.h"

#include <stdint.h>

static uint64_t end, start;
void setup()
{
	alt_puts("\n\n\n\n\n\n\n");
}

void loop()
{
	static int i = 0;
	uint64_t data[2];
	alt_puts("\n\n");
	while (ecall_recv(0, data)) {
		alt_printf("%s", (char*)data);
	}
	

        ecall_recv(1,data);
        alt_printf("Application (SPM) execution time(%d): %D cycles\n", i++,data[1] - data[0]);
        ecall_wfi();
}
