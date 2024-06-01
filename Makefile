PROJECTS=projects/hello \
	 projects/hello2 \
	 projects/cov-chan-dcache \
	 projects/cov-chan-icache \
	 projects/image-processor \
	 projects/predict-dispatch \
	 projects/predict-exec-spm \
	 projects/predict-exec-ram

all: ${PROJECTS}

${PROJECTS}:
	${MAKE} -C $@ all

clean:
	for i in common ${PROJECTS}; do \
		${MAKE} -C $$i clean; \
	done

.PHONY: all common ${PROJECTS} clean
