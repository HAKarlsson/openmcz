PROJECTS=projects/hello \
	 projects/cov-chan-dcache \
	 projects/cov-chan-icache \
	 projects/image-processor \
	 projects/predict-dispatch \
	 projects/predict-exec-spm \
	 projects/predict-exec-ram

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
