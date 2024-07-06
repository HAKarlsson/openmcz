PROJECTS=${wildcard projects/*/}

all: ${PROJECTS}

libopenmcz:
	${MAKE} -C $@ all

${PROJECTS}: libopenmcz 
	${MAKE} -C $@ all

clean:
	for i in common ${PROJECTS}; do \
		${MAKE} -C $$i clean; \
	done

.PHONY: all libopenmcz ${PROJECTS} clean
