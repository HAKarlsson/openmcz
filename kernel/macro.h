#pragma once

#define BIT(x) (1ul << (x))
#define SETBIT(x, y) ((x) | BIT(y))
#define CLEARBIT(x, y) ((x) & ~BIT(y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define TRUE 1
#define FALSE 0
