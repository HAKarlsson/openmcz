# Kernel Instruction Cache Side-Channel

In this project we setup a covert channel between zone 1 and zone 2. Zone 1 and
zone 2 have distinct memory regions, and share no IPC communication channels.
Zone 1 and zone 2 are scheduled round-robin. The covert channel uses the cache
as follows:

 - Zone 1 writes to memory regions `0x80020000 - 0x80030000` every other round-robin cycle.
 - Zone 2 measures the time it takes to writs to memory regions `0x80030000 - 0x80040000`.

If there exists a covert channel, we expect that zone 2's measured time
will have a periodic behaviour.

# Scheduler and Zone configuration

In [kernel/config.h](kernel/config.h) we have the scheduler and zone
configuration. The relevant data is in `schedule[]`:
```c
const sched_t schedule[] = {
	{ &zone1, 1000000, X},
	{ &zone2, 1000000, Y},
};
```
- If `X` is `true`, then we execute a temporal fence before dispatching zone 1.
- If `Y` is `true`, then we execute a temporal fence before dispatching zone 2.

# Testing results

Testing results on Genesys2 with CVA6+temporal fence shows that:

- If `Y=true`: The covert channel is absent.
- If `X=true` and `Y=false`: The covert channel is absent.
- If `X=false` and `Y=false`: The covert channel clearly exists.
