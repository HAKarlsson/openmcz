#ifndef TRAP_H
#define TRAP_H

#include "kernel.h"

thread_t *trap_handler(thread_t *thd, uint64_t mcause, uint64_t mtval);
void trap_entry(void);
void trap_exit(thread_t *thd);
void trap_resume(thread_t *thd);

#endif /* TRAP_H */
