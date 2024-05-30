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

include ${ROOT}/tools.mk

COMMON_INC=${ROOT}/common/inc
COMMON_LIB=${ROOT}/common/lib

CFLAGS:=-Os -g -nostartfiles
CFLAGS+=-march=rv64imac_zicsr_zifencei -mabi=lp64 -mcmodel=medany
CFLAGS+=-fdata-sections -ffunction-sections
CFLAGS+=-flto ${INC} -I${COMMON_INC}
CFLAGS+=-c -MMD
CFLAGS+=-specs=picolibc.specs

LDFLAGS =-march=rv64imac_zicsr_zifencei -mabi=lp64 -mcmodel=medany
LDFLAGS+=-flto -nostdlib -T${LINKERSCRIPT}
LDFLAGS+=-fstack-usage
LDFLAGS+=-Wl,--gc-sections
LDFLAGS+=-L${COMMON_LIB} -laltc

all: elf hex da size
elf: ${ELF}
hex: ${HEX}
da: ${DA}

clean:
	rm -f ${ELF} ${HEX} ${DA} ${OBJS} ${DEPS}

${BUILDDIR} ${OBJDIR}:
	mkdir -p $@

${OBJDIR}/%.o: %.S | ${OBJDIR}
	${CC} $< -o $@ ${CFLAGS}

${OBJDIR}/%.o: %.c | ${OBJDIR}
	${CC} $< -o $@ ${CFLAGS}

${ELF}: ${OBJS} ${LINKERSCRIPT} | ${BUILDDIR}
	${CC} -o $@ ${OBJS} ${LDFLAGS}

${HEX}: ${ELF} | ${BUILDDIR}
	${OBJCOPY} -O ihex $< $@

${DA}: ${ELF} | ${BUILDDIR}
	${OBJDUMP} -S $< > $@

size: ${ELF}
	${SIZE} $<

-include ${DEPS}

.PHONY: all clean elf hex da size
