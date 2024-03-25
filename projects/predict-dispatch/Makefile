export ROOT=${abspath ../../}

SUBDIRS=kernel im-proc uart measurer trasher

MERGED=build/merged.hex

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
