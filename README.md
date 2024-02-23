# OpenMCZ

Project is very much WIP so many planned features, documentation, and example projects are missing.

# Compilation / Testing

Currently, the kernel is pretty hardcoded to work with [PULP
CVA6](http://github.com/pulp-platform/cva6) running on a Genesys2 FPGA. I can
not really help with getting this version of CVA6 working.

The example project [hello](projects/hello) should be runnable on CVA6.
To compile the project, you should install the riscv-gnu-toolchain.
The toolchain binaries should have the prefix `riscv64-unknown-elf-`.
```bash
# Install necessary dependencies for your system (see http://github.com/riscv-collab/riscv-gnu-toolchain).
# Clone toolchain
git clone git@github.com:riscv-collab/riscv-gnu-toolchain.git
cd riscv-gnu-toolchain
./configure --enable-multilib --prefix=/opt/riscv
sudo make install
# Add /opt/riscv/bin to the PATH variable in .bashrc
```

Then you can clone this repository and compile the hello project.
```bash
git clone git@github.com:HAKarlsson/openmcz.git
cd openmcz/projects/hello
make
```

To run the hello porject on PULP's CVA6 on Genesys2:
```bash
# We have an openocd config file in this repository under openocd/cva6.cfg
openocd -f openocd/cva6.cfg

# In another terminal window, start RISC-V GDB.
# Load the hex file (merged.hex = kernel.hex + applications.hex), and start the program.
riscv64-unknown-elf-gdb
(gdb) target extended-remote :3333
(gdb) load openmcz/projects/hello/build/merged.hex
(gdb) continue
```


# OpenMZ design

OpenMCZ is a simple separation kernel for RISC-V. OpenMCZ (open multicore
zones) is a version of OpenMZ (to be) adapted for multicore processors.
Adaptations include flexible and more powerfil inter-zone communication, and yield
system calls that respect zone isolation when running on multiple cores.

## Zones

Zones are isolated system partitions that are protected using RISC-V's PMP
mechanisms. Zones can communicate with each other using explicitly defined
communications channels. This includes shared memory and the kernel's IPC
mechanism.

*Planned feature.* Each zone should have of one thread per processor core.
These threads have independent memory protection and IPC configuration.
Processes within a zone runs simultanously. Processes of separate zones are
isolated (unless explicitly allowed to communicate) and do run simultanously.

## IPC

*TODO.*

## Process scheduling

*TODO.*

# Other planned features
- Interrupt/PLIC handling.
- User Timer emulation.
