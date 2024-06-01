export ROOT=${abspath ../../}

SUBDIRS=kernel zone1 zone2

MERGED=build/hello.hex

all: ${MERGED}

${MERGED}: ${SUBDIRS}
	srec_cat ${patsubst %, build/%.hex -Intel, $^} -o $@ -Intel

${SUBDIRS}:
	${MAKE} -C $@ all

clean:
	rm -f ${MERGED}
	for i in ${SUBDIRS}; do \
		${MAKE} -C $$i clean; \
	done

.PHONY: all clean ${CLEAN} ${SUBDIRS}
