#include "altio.h"
#include "openmcz.h"

#include <stdint.h>

void setup()
{
    alt_puts("setup driver");
}

void loop()
{
    uint64_t data[2];
    data[1] = '\0';
    if (ecall_recv(0, data))
        alt_printf("%s", (char*)data);
}
