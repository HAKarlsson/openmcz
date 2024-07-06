include ../tools.mk

SRCS := openmcz.c uart.c exit.c altio.c driver/serial/uart_16550.c
OBJS := ${patsubst %.c,obj/%.o, ${SRCS}}
CFLAGS=-march=rv64imac -mabi=lp64 -mcmodel=medany -specs=picolibc.specs -Iinc
CFLAGS+=-DPLATFORM_CHESHIRE

LIB=lib/libopenmcz.a

vpath %.c src

all: ${LIB}

clean:
	rm -f ${OBJS} ${LIB}

lib/libopenmcz.a: ${OBJS}
	mkdir -p ${@D}
	${AR} cr $@ $^

obj/%.o: src/%.c
	mkdir -p ${@D}
	${CC} ${CFLAGS} -c -o $@ $<

obj/%.o: src/%.S
	mkdir -p ${@D}
	${CC} ${CFLAGS} -c -o $@ $<

.PHONY: all clean
