#include "csr.h"

.globl _start
.globl __stack_top

.section .init

_start:
        csrw    mstatus,zero
        csrw    pmpcfg0,zero
        csrw    pmpaddr0,zero
        csrw    pmpaddr1,zero
        csrw    pmpaddr2,zero
        csrw    pmpaddr3,zero
        csrw    pmpaddr4,zero
        csrw    pmpaddr5,zero
        csrw    pmpaddr6,zero
        csrw    pmpaddr7,zero

        .option push
        .option norelax
        la      gp,__global_pointer$
        .option pop
        la      sp,__stack_top

        // Zero bss
        la      t0,_bss
        la      t1,_end
        j       2f
1:      sd      zero,0(t0)
        addi    t0,t0,8
2:      bne     t0,t1,1b

/* Enable hpmcounters for zones */
        csrw    mcounteren,(MCOUNTEREN_CY | MCOUNTEREN_TM)
        csrw    scounteren,(MCOUNTEREN_CY | MCOUNTEREN_TM)

        call    kernel_init
        j       trap_exit

.section .bss.stack
.balign 8
__stack_bottom:
        .zero 64
__stack_top:
