.globl _start
.globl __stack_top

.section .init

_start:
	csrw	mstatus,zero
	csrw	mscratch,zero

	.option push
	.option norelax
	la	gp,__global_pointer$
	.option pop

	csrr	t0,mhartid
	bnez	t0,3f

	// Zero bss
	la	t0,_bss
	la	t1,_end
	j	2f
1:	sd	zero,0(t0)
	addi	t0,t0,8
2:	bne	t0,t1,1b
3:
	call	kernel_init
	call	kernel_sched
	j	trap_exit

.end
