BUILDDIR?=.
LINKERSCRIPT?=default.ld
PROGRAM?=foobar

OBJDIR?=${BUILDDIR}/obj-${PROGRAM}

ELF := ${BUILDDIR}/${PROGRAM}.elf
HEX := ${BUILDDIR}/${PROGRAM}.hex
DA  := ${BUILDDIR}/${PROGRAM}.da

OBJS ?=${patsubst %.S,${OBJDIR}/%.o,${filter %.S, ${SRCS}}} \
       ${patsubst %.c,${OBJDIR}/%.o,${filter %.c, ${SRCS}}}
DEPS ?=${patsubst %.o,%.d,${OBJS}}

CC=riscv64-unknown-elf-gcc
OBJCOPY=riscv64-unknown-elf-objcopy
OBJDUMP=riscv64-unknown-elf-objdump

CFLAGS:=-O2 -g -nostartfiles
CFLAGS+=-march=rv64imac_zicsr -mabi=lp64 -mcmodel=medany
CFLAGS+=${INC}

all: ${ELF} ${HEX} ${DA}

clean:
	rm -f ${ELF} ${HEX} ${DA} ${OBJS} ${DEPS}

${BUILDDIR} ${OBJDIR}:
	mkdir -p $@

${OBJDIR}/%.o: %.S | ${OBJDIR}
	${CC} ${CFLAGS} -c -MMD -o $@ $<

${OBJDIR}/%.o: %.c | ${OBJDIR}
	${CC} ${CFLAGS} -c -MMD -o $@ $<

${ELF}: ${OBJS} ${LINKERSCRIPT} | ${BUILDDIR}
	${CC} ${CFLAGS} -T${LINKERSCRIPT} -o $@ ${OBJS}

${HEX}: ${ELF} | ${BUILDDIR}
	${OBJCOPY} -O ihex $< $@

${DA}: ${ELF} | ${BUILDDIR}
	${OBJDUMP} -S $< > $@

-include ${DEPS}

.PHONY: all clean
