#ifndef OPENMCZ_H
#define OPENMCZ_H

static inline int ecall_yield(void)
{
	register unsigned long t0 __asm__("t0");
	register unsigned long a0 __asm__("a0");
	t0 = 0;
	__asm__ volatile("ecall" : "=r"(a0) :"r"(t0));
	return a0;
}

static inline int ecall_wfi(void)
{
	register unsigned long t0 __asm__("t0");
	register unsigned long a0 __asm__("a0");
	t0 = 1;
	__asm__ volatile("ecall" : "=r"(a0) :"r"(t0));
	return a0;
}

static inline int ecall_send(unsigned long ch, unsigned long *msg)
{
	register unsigned long t0 __asm__("t0");
	register unsigned long a0 __asm__("a0");
	register unsigned long a1 __asm__("a1");
	t0 = 2;
	a0 = ch;
	a1 = msg[0];
	__asm__ volatile("ecall" : "+r"(a0) : "r"(t0), "r"(a1));
	return a0;
}

static inline int ecall_recv(unsigned long ch, unsigned long *msg)
{
	register unsigned long t0 __asm__("t0");
	register unsigned long a0 __asm__("a0");
	register unsigned long a1 __asm__("a1");
	t0 = 3;
	a0 = ch;
	__asm__ volatile("ecall" : "+r"(a0), "=r"(a1) : "r"(t0));
	if (a0)
		msg[0] = a1;
	return a0;
}

static inline int ecall_write(unsigned long ch, unsigned long *msg)
{
	register unsigned long t0 __asm__("t0");
	register unsigned long a0 __asm__("a0");
	register unsigned long a1 __asm__("a1");
	t0 = 4;
	a0 = ch;
	a1 = msg[0];
	__asm__ volatile("ecall" : "+r"(a0) : "r"(t0), "r"(a1));
	return a0;
}

static inline int ecall_read(unsigned long ch, unsigned long *msg)
{
	register unsigned long t0 __asm__("t0");
	register unsigned long a0 __asm__("a0");
	register unsigned long a1 __asm__("a1");
	t0 = 5;
	a0 = ch;
	__asm__ volatile("ecall" : "+r"(a0), "+r"(a1) : "r"(t0));
	msg[0] = a1;
	return a0;
}
#endif /* OPENMCZ_H */
