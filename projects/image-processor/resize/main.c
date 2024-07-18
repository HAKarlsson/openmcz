#include "../shared.h"
#include "openmcz.h"

void setup()
{
}

void loop()
{
    resize(shared->resized, shared->greyed, 64, 64);
    ecall_yield();
}
