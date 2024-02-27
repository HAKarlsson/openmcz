export ROOT=${abspath ../../}

SUBDIRS=kernel grey resize sobel ascii printer

CLEAN=${addsuffix .clean, ${SUBDIRS} bare-metal}
MERGED=build/merged.hex

all: ${MERGED} bare-metal

${MERGED}: ${SUBDIRS}
	srec_cat ${patsubst %, build/%.hex -Intel, $^} -o $@ -Intel

${SUBDIRS} bare-metal:
	${MAKE} -C $@ all

${CLEAN}:
	${MAKE} -C ${basename $@} clean

clean: ${CLEAN}

.PHONY: all clean ${CLEAN} ${SUBDIRS} bare-metal
