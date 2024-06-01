include ${ROOT}/tools.mk

PROGRAM=kernel
KERNEL=${ROOT}/kernel

vpath %.c ${KERNEL}
vpath %.S ${KERNEL}

BUILDDIR?=.
LINKERSCRIPT?=default.ld

ELF := ${BUILDDIR}/${PROGRAM}.elf
HEX := ${BUILDDIR}/${PROGRAM}.hex
DA  := ${BUILDDIR}/${PROGRAM}.da

CFLAGS:=-Os -g -nostartfiles
CFLAGS+=-march=rv64imafdc_zicsr_zifencei -mabi=lp64d -mcmodel=medany
CFLAGS+=-flto ${INC}
CFLAGS+=-MMD
CFLAGS+=-specs=nano.specs
CFLAGS+=-I. -I${KERNEL} -I${ROOT}/libopenmcz
CFLAGS+=-T${LINKERSCRIPT}
CFLAGS+=-fstack-usage -Wstack-usage=0

SRCS=head.S trap.S ecall.c kernel.c trap.c

all: elf hex da size
elf: ${ELF}
hex: ${HEX}
da: ${DA}

clean:
	rm -f ${ELF} ${HEX} ${DA}

${BUILDDIR} ${OBJDIR}:
	mkdir -p $@

${ELF}: ${SRCS} | ${BUILDDIR}
	${CC} -o $@ $^ ${CFLAGS}

${HEX}: ${ELF} | ${BUILDDIR}
	${OBJCOPY} -O ihex $< $@

${DA}: ${ELF} | ${BUILDDIR}
	${OBJDUMP} -S $< > $@

size: ${ELF}
	${SIZE} $<

.PHONY: all clean elf hex da size
