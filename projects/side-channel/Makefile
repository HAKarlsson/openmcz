export ROOT=${abspath ../../}

SUBDIRS=kernel zone1 zone2

ALL=${addsuffix .all, ${SUBDIRS}}
CLEAN=${addsuffix .clean, ${SUBDIRS}}
HEX=${patsubst %,build/%.hex, ${SUBDIRS}}
ELF=${patsubst %,build/%.elf, ${SUBDIRS}}
MERGED=build/merged.hex

all: ${MERGED}

%.all: %
	${MAKE} -C $<

%.clean: %
	${MAKE} -C $< clean

build/%.hex: %.all
build/%.elf: %.all
build/%.da: %.all

${MERGED}: ${HEX}
	srec_cat ${patsubst %, % -Intel, ${HEX}} -o $@ -Intel

${HEX}: build/%.hex: %.all

clean: ${CLEAN}

.PHONY: all ${SUBDIRS} clean
