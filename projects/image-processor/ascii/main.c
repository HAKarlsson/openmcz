#include "api/openmz.h"
#include "../shared.h"

#include <stdint.h>


void setup()
{
}


void loop()
{
        ascii(shared->asciied, shared->sobeled, 62, 30);
	ecall_yield();
}
