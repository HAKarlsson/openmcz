#pragma once

#define PMP_NAPOT(base, size) (((base) | ((size) / 2 - 1)) >> 2)
