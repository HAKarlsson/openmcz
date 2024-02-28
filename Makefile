PROJECTS=projects/hello projects/side-channel projects/image-processor projects/predictability

all: common ${PROJECTS}

common:
	${MAKE} -C $@ all

${PROJECTS}: common
	${MAKE} -C $@ all

clean:
	for i in common ${PROJECTS}; do \
		${MAKE} -C $$i clean; \
	done

.PHONY: all common ${PROJECTS} clean
