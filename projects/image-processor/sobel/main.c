#include "../shared.h"
#include "api/openmz.h"

void setup()
{
}

void loop()
{
	sobel(shared->sobeled, shared->resized, 64, 32);
	ecall_yield();
}
