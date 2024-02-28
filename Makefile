PROJECTS=projects/hello projects/side-channel projects/image-processor projects/predictability

all: common ${PROJECTS}

common ${PROJECTS}:
	${MAKE} -C $@ all

clean:
	for i in common ${PROJECTS}; do \
		${MAKE} -C $$i clean; \
	done

.PHONY: all ${PROJECTS} clean
