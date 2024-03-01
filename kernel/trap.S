#include "csr.h"

.globl trap_entry
.globl trap_exit

.section .text.trap

.balign 16
trap_entry:
        # Swap the user with kernel sp
        csrrw   tp,mscratch,tp
        # Save the process context to stack.
        #sd      pc,(8*0)(tp)
        sd      ra,(8*1)(tp)
        sd      sp,(8*2)(tp)
        sd      gp,(8*3)(tp)
        #sd      tp,(8*4)(tp)
        sd      t0,(8*5)(tp)
        sd      t1,(8*6)(tp)
        sd      t2,(8*7)(tp)
        sd      s0,(8*8)(tp)
        sd      s1,(8*9)(tp)
        sd      a0,(8*10)(tp)
        sd      a1,(8*11)(tp)
        sd      a2,(8*12)(tp)
        sd      a3,(8*13)(tp)
        sd      a4,(8*14)(tp)
        sd      a5,(8*15)(tp)
        sd      a6,(8*16)(tp)
        sd      a7,(8*17)(tp)
        sd      s2,(8*18)(tp)
        sd      s3,(8*19)(tp)
        sd      s4,(8*20)(tp)
        sd      s5,(8*21)(tp)
        sd      s6,(8*22)(tp)
        sd      s7,(8*23)(tp)
        sd      s8,(8*24)(tp)
        sd      s9,(8*25)(tp)
        sd      s10,(8*26)(tp)
        sd      s11,(8*27)(tp)
        sd      t3,(8*28)(tp)
        sd      t4,(8*29)(tp)
        sd      t5,(8*30)(tp)
        sd      t6,(8*31)(tp)

        csrr    t1,mepc
        csrrw   t2,mscratch,zero
        sd      t1,(8*0)(tp)    # Store PC
        sd      t2,(8*4)(tp)    # Store TP

        .option push
        .option norelax
        la      gp,__global_pointer$
        .option pop
        la      sp,__stack_top

        # Check interrupt
        csrr    t2,mcause
        bltz    t2,trap_interrupt

        la      ra,trap_exit

        # Check exception (excl. ecall)
        li      t3,0x8
        bne     t2,t3,trap_exception

trap_ecall:
        # Check if valid ecall
        li      t3,0x4
        bgeu    t0,t3,trap_exception

        # Increment PC by 4
        addi    t1,t1,4
        sd      t1,(8*0)(tp)

        # Jump ecall handler
1:      auipc   t1,%pcrel_hi(_ecall_table)
        slli    t0,t0,2
        add     t1,t1,t0
        jalr    zero,%pcrel_lo(1b)(t1)

.option push
.option norvc
_ecall_table:
        j       ecall_yield
        j       ecall_wfi
        j       ecall_send
        j       ecall_recv
.option pop

trap_exception:
        csrr    a0,mcause
        csrr    a1,mepc
        csrr    a2,mtval
        j       exception_handler

trap_interrupt:
        call    kernel_yield

trap_exit:
        # Load the process context from stack.
        ld      t0,(8*0)(tp)    # Restore PC
        ld      t1,(8*4)(tp)    # Restore TP
        csrw    mepc,t0
        csrw    mscratch,t1
        ld      t6,(8*31)(tp)
        ld      t5,(8*30)(tp)
        ld      t4,(8*29)(tp)
        ld      t3,(8*28)(tp)
        ld      s11,(8*27)(tp)
        ld      s10,(8*26)(tp)
        ld      s9,(8*25)(tp)
        ld      s8,(8*24)(tp)
        ld      s7,(8*23)(tp)
        ld      s6,(8*22)(tp)
        ld      s5,(8*21)(tp)
        ld      s4,(8*20)(tp)
        ld      s3,(8*19)(tp)
        ld      s2,(8*18)(tp)
        ld      a7,(8*17)(tp)
        ld      a6,(8*16)(tp)
        ld      a5,(8*15)(tp)
        ld      a4,(8*14)(tp)
        ld      a3,(8*13)(tp)
        ld      a2,(8*12)(tp)
        ld      a1,(8*11)(tp)
        ld      a0,(8*10)(tp)
        ld      s1,(8*9)(tp)
        ld      s0,(8*8)(tp)
        ld      t2,(8*7)(tp)
        ld      t1,(8*6)(tp)
        ld      t0,(8*5)(tp)
        ld      ra,(8*1)(tp)
        ld      gp,(8*3)(tp)
        ld      sp,(8*2)(tp)
        csrrw   tp,mscratch,tp
        mret

