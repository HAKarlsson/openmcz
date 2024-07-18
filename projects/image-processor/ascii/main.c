#include "../shared.h"
#include "openmcz.h"

#include <stdint.h>

void setup()
{
}

void loop()
{
    ascii(shared->asciied, shared->sobeled, 62, 30);
    ecall_yield();
}
