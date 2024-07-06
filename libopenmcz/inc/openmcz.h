#ifndef OPENMCZ_H
#define OPENMCZ_H
#include <stdint.h>

int ecall_yield(void);
int ecall_wfi(void);
int ecall_send(uint64_t ch, uint64_t msg);
int ecall_recv(uint64_t ch, uint64_t *msg);
int ecall_write(uint64_t ch, uint64_t offset, uint64_t msg);
int ecall_read(uint64_t ch, uint64_t offset, uint64_t *msg);

#endif /* OPENMCZ_H */
