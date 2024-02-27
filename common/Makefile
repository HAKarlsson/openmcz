include ../tools.mk

ALTC_SRCS := ${wildcard src/altc/*.[cS]}
ALTC_OBJS := ${patsubst src/%.c,obj/%.o, ${filter %.c, ${ALTC_SRCS}}} \
	     ${patsubst src/%.S,obj/%.o, ${filter %.S, ${ALTC_SRCS}}}
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

obj/%.o: src/%.S
	mkdir -p ${@D}
	${CC} ${CFLAGS} -c -o $@ $<

.PHONY: all clean
