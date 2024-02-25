PROGRAM=kernel
LINKERSCRIPT=${KERNEL}/default.ld
KERNEL=${ROOT}/kernel

vpath %.c ${KERNEL}
vpath %.S ${KERNEL}

SRCS=head.S trap.S ecall.c exception.c interrupt.c kernel.c time.c
INC=-I${KERNEL} -I.

include ${ROOT}/default.mk
