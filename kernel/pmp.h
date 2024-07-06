#ifndef PMP_H
#define PMP_H

#define PMP_R 0x1
#define PMP_W 0x2
#define PMP_X 0x4
#define PMP_RW (PMP_R | PMP_W)
#define PMP_RX (PMP_R | PMP_X)
#define PMP_RXW (PMP_R | PMP_X | PMP_W)

#define PMP_MODE_TOR 0x08
#define PMP_MODE_NA4 0x10
#define PMP_MODE_NAPOT 0x18

#define PMP_CFG(i, mode, rwx) ((mode | rwx) << (i * 8))

#define PMP_ADDR_NAPOT(base, size) (((base) | ((size) / 2 - 1)) >> 2)
#define PMP_ADDR_NA4(addr)
#define PMP_ADDR_TOR(addr) (addr >> 2)

#endif /* PMP_H */
