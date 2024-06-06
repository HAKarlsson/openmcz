.globl trap_entry
.globl trap_exit

.section .text.trap

.balign 16
trap_entry:
	/* Swap the user with kernel a0 */
	csrrw	a0,mscratch,a0
	/* Save the thread context to thread control block. */
	/* sd	pc,(8*0)(a0) */
	sd	ra,(8*1)(a0)
	sd	sp,(8*2)(a0)
	sd	gp,(8*3)(a0)
	sd	tp,(8*4)(a0)
	sd	t0,(8*5)(a0)
	sd	t1,(8*6)(a0)
	sd	t2,(8*7)(a0)
	sd	s0,(8*8)(a0)
	sd	s1,(8*9)(a0)
	/* sd	a0,(8*10)(a0) */
	sd	a1,(8*11)(a0)
	sd	a2,(8*12)(a0)
	sd	a3,(8*13)(a0)
	sd	a4,(8*14)(a0)
	sd	a5,(8*15)(a0)
	sd	a6,(8*16)(a0)
	sd	a7,(8*17)(a0)
	sd	s2,(8*18)(a0)
	sd	s3,(8*19)(a0)
	sd	s4,(8*20)(a0)
	sd	s5,(8*21)(a0)
	sd	s6,(8*22)(a0)
	sd	s7,(8*23)(a0)
	sd	s8,(8*24)(a0)
	sd	s9,(8*25)(a0)
	sd	s10,(8*26)(a0)
	sd	s11,(8*27)(a0)
	sd	t3,(8*28)(a0)
	sd	t4,(8*29)(a0)
	sd	t5,(8*30)(a0)
	sd	t6,(8*31)(a0)

	/* Save user pc and a0 */
	csrr	t1,mepc
	csrrw	t2,mscratch,zero
	sd	t1,(8*0)(a0)
	sd	t2,(8*10)(a0)

2:
	/* Load kernel global pointer */
	.option push
	.option norelax
	la	gp,__global_pointer$
	.option pop

	/* Call the trap handler */
	csrr	a1,mcause
	csrr	a2,mtval
	call	trap_handler

	csrr	t0,mip
	andi	t0,t0,0x80
	li	a1,0x8000000000000007
	bnez	t0,trap_handler
trap_exit:
	/* Write user pc to mscratch */
	ld	t0,(8*0)(a0)
	ld	t1,(8*10)(a0)
	csrw	mepc,t0
	csrw	mscratch,t1

	/* Load the thread context from thread control block. */
	/* ld	pc,(8*0)(a0) */
	ld	ra,(8*1)(a0)
	ld	sp,(8*2)(a0)
	ld	gp,(8*3)(a0)
	ld	tp,(8*4)(a0)
	ld	t0,(8*5)(a0)
	ld	t1,(8*6)(a0)
	ld	t2,(8*7)(a0)
	ld	s0,(8*8)(a0)
	ld	s1,(8*9)(a0)
	/* ld	a0,(8*10)(a0) */
	ld	a1,(8*11)(a0)
	ld	a2,(8*12)(a0)
	ld	a3,(8*13)(a0)
	ld	a4,(8*14)(a0)
	ld	a5,(8*15)(a0)
	ld	a6,(8*16)(a0)
	ld	a7,(8*17)(a0)
	ld	s2,(8*18)(a0)
	ld	s3,(8*19)(a0)
	ld	s4,(8*20)(a0)
	ld	s5,(8*21)(a0)
	ld	s6,(8*22)(a0)
	ld	s7,(8*23)(a0)
	ld	s8,(8*24)(a0)
	ld	s9,(8*25)(a0)
	ld	s10,(8*26)(a0)
	ld	s11,(8*27)(a0)
	ld	t3,(8*28)(a0)
	ld	t4,(8*29)(a0)
	ld	t5,(8*30)(a0)
	ld	t6,(8*31)(a0)
	/* Save thread control block and load user a0 */
	csrrw	a0,mscratch,a0
	mret
.end
