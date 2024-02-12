all:
	${MAKE} -C kernel all
	${MAKE} -C zone1 all
	${MAKE} -C zone2 all
	srec_cat build/kernel.hex -Intel build/zone1.hex -Intel build/zone2.hex -Intel -o build/merged.hex -Intel

clean:
	${MAKE} -C kernel clean
	${MAKE} -C zone1 clean
	${MAKE} -C zone2 clean

.PHONY: all clean
