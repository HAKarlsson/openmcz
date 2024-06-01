BUILDDIR?=.
LINKERSCRIPT?=default.ld
PROGRAM?=foobar

ELF := ${BUILDDIR}/${PROGRAM}.elf
HEX := ${BUILDDIR}/${PROGRAM}.hex
DA  := ${BUILDDIR}/${PROGRAM}.da

DEPS ?=${patsubst %.o,%.d,${OBJS}}

include ${ROOT}/tools.mk

COMMON_INC=${ROOT}/common/inc
COMMON_LIB=${ROOT}/common/lib

CFLAGS:=-Os -g
CFLAGS+=-march=rv64imac_zicsr_zifencei -mabi=lp64 -mcmodel=medany
CFLAGS+=${INC}
CFLAGS+=-MMD
CFLAGS+=-specs=nano.specs -nostartfiles
CFLAGS+=-I${ROOT}/common/inc
CFLAGS+=-L${ROOT}/common/lib -laltc
CFLAGS+=-T${LINKERSCRIPT}

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
