export ROOT=${abspath ../../}

SUBDIRS=kernel grey resize sobel ascii printer

CLEAN=${addsuffix .clean, ${SUBDIRS}}
MERGED=build/merged.hex

all: ${MERGED}

${MERGED}: ${SUBDIRS}
	srec_cat ${patsubst %, build/%.hex -Intel, $^} -o $@ -Intel

${SUBDIRS}:
	${MAKE} -C $@ all

${CLEAN}:
	${MAKE} -C ${basename $@} clean

clean: ${CLEAN}

.PHONY: all clean ${CLEAN} ${SUBDIRS}
