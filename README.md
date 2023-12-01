# risc-v-sim

This is a simulator that is able to run programs using the RV32i Base Integer Instruction Set, Version 2.
(https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)

Instructions of the instruction set that are not supported/implemented: ```fence```, ```fence.i```, ```ebreak```, ```csrrw```, ```csrrs```, ```csrrc```, ```csrrwi```, ```csrrsi``` and ```csrrci```.
```ecall``` is only supported for terminating execution, with no differentiation of arguments.

## Requirements
The simulator works on any operating system with cmake v2.23 or greater, as well as a c compiler - tested with gcc v11.4.0.

## How to run the simulator
Open up a terminal in the project root.

Execute the following commands:
```bash
cmake .
make
```

The program can now be run with the following three commands:
```bash
./risc_v_sim
./risc_v_sim t
./risc_v_sim <filepath>
```
The command without options runs a demo program, with the sourcecode specified by ```./demo.s```.
The t option runs the full test suite.
The filepath option runs the specified file, example:
```bash
./risc_v_sim ./test/task4/t11.bin
```
runs the selected program and creates the file ```./test/task4/t11Result.res``` which contains the contents of the 32 registers after execution.
