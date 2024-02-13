#include "kernel.h"
#include "macro.h"

void ecall_yield()
{
	kernel_yield();
}

void ecall_wfi()
{
	wfi();
}

void ecall_send(uint64_t ch, uint64_t msg0, uint64_t msg1)
{
	if (ch >= current->n_chan_send) {
		current->regs.a0 = 0;
		return;
	}

	channel_t *chan = current->chan_send[ch];
	if (chan->head - chan->tail == chan->size) {
		current->regs.a0 = 0;
		return;
	}

	chan->buf[chan->head % chan->size] = msg0;
	chan->buf[(chan->head + 1) % chan->size] = msg1;
	chan->head += 2;
	current->regs.a0 = 1;
}

void ecall_recv(uint64_t ch)
{
	if (ch >= current->n_chan_recv) {
		current->regs.a0 = 0;
		return;
	}

	channel_t *chan = current->chan_recv[ch];
	if (chan->tail == chan->head) {
		current->regs.a0 = 0;
		return;
	}

	current->regs.a1 = chan->buf[chan->tail % chan->size];
	current->regs.a2 = chan->buf[(chan->tail + 1) % chan->size];
	chan->tail += 2;
	current->regs.a0 = 1;
}
