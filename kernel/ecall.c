#include "csr.h"
#include "kernel.h"
#include "wfi.h"

#include <stdbool.h>

static inline bool bit_is_set(uint64_t val, uint64_t bit)
{
	return (val >> bit) & 1;
}

static inline bool queue_acquire(queue_t *q)
{
#if N_HARTS > 1 
	while (__atomic_fetch_or(&q->lock, 1, __ATOMIC_ACQUIRE)) {
		// TODO: check for preemption, return false if
		if (csrr_mip() & csrr_mie())
			return false;
	}
	return true;
#else
	return true;
#endif
}

static inline void queue_release(queue_t *q)
{
#if N_HARTS > 1 
	__atomic_store_n(&q->lock, 0, __ATOMIC_RELEASE);
#endif
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

static thread_t *ecall_enq(thread_t *thd)
{
	uint64_t queue_id = thd->regs.a0;
	uint64_t value = thd->regs.a1;
	queue_t *queue = queues + queue_id;

	thd->regs.a0 = 0;

	// Check permission.
	if (!bit_is_set(thd->queue_recv, queue_id))
		return thd;

	// Attempt to acquire lock.
	if (!queue_acquire(queue))
		return thd;

	// Check if full
	if (queue->head == queue->tail + queue->size) {
		queue_release(queue);
		return thd;
	}

	// Success, enqueue data data.
	thd->regs.a0 = 1;
	queue->buf[queue->tail++ % queue->size] = value;
	queue_release(queue);
	return thd;
}

static thread_t *ecall_deq(thread_t *thd)
{
	uint64_t queue_id = thd->regs.a0;
	queue_t *queue = queues + queue_id;

	// Fail return values.
	thd->regs.a0 = 0;
	thd->regs.a1 = 0;

	// Check permission.
	if (!bit_is_set(thd->queue_recv, queue_id))
		return thd;

	// Attempt to acquire lock.
	if (!queue_acquire(queue))
		return thd;

	// Check if empty
	if (queue->head == queue->tail) {
		queue_release(queue);
		return thd;
	}

	// Success, dequeue data data.
	thd->regs.a0 = 1;
	thd->regs.a1 = queue->buf[queue->tail++ % queue->size];
	queue_release(queue);
	return thd;
}

static thread_t *ecall_write(thread_t *thd)
{
	uint64_t buffer_id = thd->regs.a0;
	uint64_t offset = thd->regs.a1;
	uint64_t value = thd->regs.a2;
	buffer_t *buffer = buffers + buffer_id;

	// Default return values.
	thd->regs.a0 = 0;

	// Check permission.
	if (!bit_is_set(thd->buffer_write, buffer_id))
		return thd;

	// Check offset.
	if (offset >= buffer->size) 
		return thd;
		
	// Success, write to buffer.
	thd->regs.a0 = 1;
	buffer->buf[offset] = value;
	return thd;
}

static thread_t *ecall_read(thread_t *thd)
{
	uint64_t buffer_id = thd->regs.a0;
	uint64_t offset = thd->regs.a1;
	buffer_t *buffer = buffers + buffer_id;

	// Fail return values.
	thd->regs.a0 = 0;
	thd->regs.a1 = 0;

	// Check permission.
	if (!bit_is_set(thd->buffer_read, buffer_id))
		return thd;

	// Check offset.
	if (offset >= buffer->size)
		return thd;

	// Success, read from buffer.
	thd->regs.a0 = 1;
	thd->regs.a1 = buffer->buf[offset];
	return thd;
}

thread_t *ecall_handler(thread_t *thd)
{
	uint64_t syscall_nr = thd->regs.a7;
	thd->regs.pc += 4;
	switch (syscall_nr) {
	case 0:
		return ecall_yield(thd);
	case 1:
		return ecall_wfi(thd);
	case 2:
		return ecall_enq(thd);
	case 3:
		return ecall_deq(thd);
	case 4:
		return ecall_write(thd);
	case 5:
		return ecall_read(thd);
	default:
		return ecall_failure(thd);
	}
}
