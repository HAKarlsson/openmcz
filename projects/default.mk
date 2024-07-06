BUILDDIR?=.
LINKERSCRIPT?=default.ld
PROGRAM?=foobar

ELF := ${BUILDDIR}/${PROGRAM}.elf
HEX := ${BUILDDIR}/${PROGRAM}.hex
DA  := ${BUILDDIR}/${PROGRAM}.da

DEPS ?=${patsubst %.o,%.d,${OBJS}}

include ${ROOT}/tools.mk

CFLAGS:=-Os -g
CFLAGS+=-march=rv64imac_zicsr_zifencei -mabi=lp64 -mcmodel=medany
CFLAGS+=${INC}
CFLAGS+=-nostartfiles -specs=picolibc.specs 
CFLAGS+=-I${ROOT}/libopenmcz/inc
CFLAGS+=-L${ROOT}/libopenmcz/lib --oslib=openmcz
CFLAGS+=-T${LINKERSCRIPT} -Wl,--gc-sections,-flto
CFLAGS+=-MMD -flto

all: elf hex da size
elf: ${ELF}
hex: ${HEX}
da: ${DA}

clean:
	rm -f ${ELF} ${HEX} ${DA} ${OBJS} ${DEPS}

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

-include ${DEPS}

.PHONY: all clean elf hex da size
