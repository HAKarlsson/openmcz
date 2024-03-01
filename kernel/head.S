#include "csr.h"

.globl _start
.globl __stack_top

.section .init

_start:
        li      x1,0
        li      x2,0
        li      x3,0
        li      x4,0
        li      x5,0
        li      x6,0
        li      x7,0
        li      x8,0
        li      x9,0
        li      x10,0
        li      x11,0
        li      x12,0
        li      x13,0
        li      x14,0
        li      x15,0
        li      x16,0
        li      x17,0
        li      x18,0
        li      x19,0
        li      x20,0
        li      x21,0
        li      x22,0
        li      x23,0
        li      x24,0
        li      x25,0
        li      x26,0
        li      x27,0
        li      x28,0
        li      x29,0
        li      x30,0
        li      x31,0
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
        .zero 512
__stack_top:
