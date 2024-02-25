include ../tools.mk

ALTC_SRCS := ${wildcard src/altc/*.c}
ALTC_OBJS := ${patsubst src/%.c,obj/%.o, ${ALTC_SRCS}}
CFLAGS=-march=rv64imac -mabi=lp64 -mcmodel=medany
CFLAGS+=-Iinc

all: lib/libaltc.a

clean:

lib/libaltc.a: ${ALTC_OBJS}
	mkdir -p ${@D}
	${AR} cr $@ $^

obj/%.o: src/%.c
	mkdir -p ${@D}
	${CC} ${CFLAGS} -c -o $@ $<

.PHONY: all clean
