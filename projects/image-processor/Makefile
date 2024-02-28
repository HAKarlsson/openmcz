export ROOT=${abspath ../../}

SUBDIRS=kernel grey resize sobel ascii uart

MERGED=build/merged.hex

all: ${MERGED} bare-metal

${MERGED}: ${SUBDIRS}
	srec_cat ${patsubst %, build/%.hex -Intel, $^} -o $@ -Intel

${SUBDIRS} bare-metal:
	${MAKE} -C $@ all

clean:
	rm -f ${MERGED}
	for i in bare-metal ${SUBDIRS}; do \
		${MAKE} -C $$i clean; \
	done

.PHONY: all clean ${CLEAN} ${SUBDIRS} bare-metal
