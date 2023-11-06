#include <malloc.h>
#include <stdio.h>
#include "simulator.h"

void initialize(Simulator *simulator, int memorySize) {
    simulator->memory = malloc(sizeof(Memory));
    simulator->memory->startAddress = malloc(sizeof(int) * memorySize);
    simulator->memory->size = memorySize;
    simulator->processor = malloc(sizeof(Processor));
    initializeProcessor(simulator->processor);
}

void tearDown(Simulator *simulator) {
    free(simulator->memory->startAddress);
    free(simulator->memory);
    tearDownProcessor(simulator->processor);
    free(simulator->processor);
}

void printRegisters(Simulator *simulator) {
    Register *registers = simulator->processor->registers;
    char *registerNames[] = {"zero", "ra\t", "sp\t", "gp\t", "tp\t", "t0\t", "t1\t",
                             "t2\t", "s0/fp", "s1\t", "a0\t", "a1\t", "a2\t", "a3\t",
                             "a4\t", "a5\t", "a6\t", "a7\t", "s2\t", "s3\t", "s4\t",
                             "s5\t", "s6\t", "s7\t", "s8\t", "s9\t", "s10\t", "s11\t",
                             "t3\t", "t4\t", "t5\t", "t6\t"};
    printf("Register\tName\t\tDecimal\t\tHexadecimal\n");
    for (int i = 0; i < 32; ++i) {
        printf("x%i\t\t\t%s\t\t%i\t\t\t0x%x\n", i, registerNames[i], (registers + i)->data, (registers + i)->data);
    }
}

void runTests(Simulator *simulator) {

}

void reset(Simulator *simulator) {

}

void loadProgram(Simulator *simulator, char *path) {

}

void run(Simulator *simulator) {

}
