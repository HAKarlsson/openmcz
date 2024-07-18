#include "../shared.h"
#include "openmcz.h"

void setup()
{
}

void loop()
{
    sobel(shared->sobeled, shared->resized, 64, 32);
    ecall_yield();
}
