#include "csr.h"
#include "kernel.h"
#include "wfi.h"

#include <stdbool.h>

static inline bool bit_is_set(uint64_t val, uint64_t bit)
{
	return (val >> bit) & 1;
}

static thread_t *ecall_failure(thread_t *thd)
{
	thd->regs.a0 = 0;
	return thd;
}

static thread_t *ecall_yield(thread_t *thd)
{
	return kernel_sched();
}

static thread_t *ecall_wfi(thread_t *thd)
{
	thd->regs.a0 = 1;
	while (!(csrr_mip() & csrr_mie()))
		wfi();
	return thd;
}

static thread_t *ecall_send(thread_t *thd)
{
	uint64_t queue_id = thd->regs.a0;
	queue_t *q = queues + queue_id;

	thd->regs.a0 = 0;

	if (!bit_is_set(thd->queue_send, queue_id))
		return thd; /* Thread lacks permission to use queue */

	uint64_t head = __atomic_load_n(&q->head, __ATOMIC_SEQ_CST);
	uint64_t tail = __atomic_load_n(&q->tail, __ATOMIC_SEQ_CST);
	if (head - tail == q->size)
		return thd;

	/* Queue has space */
	thd->regs.a0 = 1;
	__atomic_store_n(&q->buf[head % q->size], thd->regs.a1, __ATOMIC_SEQ_CST);
	__atomic_store_n(&q->head, head + 1, __ATOMIC_SEQ_CST);
	return thd;
}

static thread_t *ecall_recv(thread_t *thd)
{
	uint64_t queue_id = thd->regs.a0;
	queue_t *q = queues + queue_id;

	thd->regs.a0 = 0;
	thd->regs.a1 = 0;

	if (!bit_is_set(thd->queue_recv, queue_id))
		return thd; /* Thread lacks permission to use queue */

	uint64_t head = __atomic_load_n(&q->head, __ATOMIC_SEQ_CST);
	uint64_t tail = __atomic_load_n(&q->tail, __ATOMIC_SEQ_CST);

	if (head == tail) /* Queue is empty */
		return thd;
	thd->regs.a0 = 1;
	thd->regs.a1 = __atomic_load_n(&q->buf[tail % q->size], __ATOMIC_SEQ_CST);
	__atomic_store_n(&q->tail, tail + 1, __ATOMIC_SEQ_CST);
	return thd;
}

static thread_t *ecall_write(thread_t *thd)
{
	uint64_t buffer_id = thd->regs.a0;
	buffer_t *buffer = buffers + buffer_id;
	if (!bit_is_set(thd->buffer_write, buffer_id)) {
		/* Thread lacks permission to use buffer */
		thd->regs.a0 = 0;
	} else {
		thd->regs.a0 = 1;
		buffer->buf[0] = thd->regs.a1;
	}
	return thd;
}

static thread_t *ecall_read(thread_t *thd)
{
	uint64_t buffer_id = thd->regs.a0;
	buffer_t *buffer = buffers + buffer_id;
	if (!bit_is_set(thd->buffer_read, buffer_id)) {
		/* Thread lacks permission to use buffer */
		thd->regs.a0 = 0;
	} else {
		thd->regs.a0 = 1;
		buffer->buf[0] = thd->regs.a1;
	}
	return thd;
}

thread_t *ecall_handler(thread_t *thd)
{
	uint64_t syscall_nr = thd->regs.t0;
	thd->regs.pc += 4;
	switch (syscall_nr) {
	case 0:
		return ecall_yield(thd);
	case 1:
		return ecall_wfi(thd);
	case 2:
		return ecall_send(thd);
	case 3:
		return ecall_recv(thd);
	case 4:
		return ecall_write(thd);
	case 5:
		return ecall_read(thd);
	default:
		return ecall_failure(thd);
	}
}
