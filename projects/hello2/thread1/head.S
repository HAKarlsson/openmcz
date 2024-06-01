.globl _start
.globl __stack_top
.extern setup
.extern loop

.section .init

_start:
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

        la      ra,loop
        tail    setup
