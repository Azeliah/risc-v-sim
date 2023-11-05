#include <malloc.h>
#include <stdio.h>
#include "simulator.h"

void initialize(Simulator *simulator, int memorySize) {
    simulator->memory = malloc(sizeof(int) * memorySize);
    simulator->processor = malloc(sizeof(Processor));
    initializeProcessor(simulator->processor);
}

void tearDown(Simulator *simulator) {
    free(simulator->memory);
    tearDownProcessor(simulator->processor);
    free(simulator->processor);
}

void printRegisters(Simulator *simulator) {
    Register *registers = simulator->processor->registers;
    char *registerNames[] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
                             "s0/fp", "s1", "a0", "a1", "a2", "a3", "a4",
                             "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6",
                             "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5",
                             "t6"};
    printf("Register\tName\tDecimal\t\tHexadecimal\n");
    for (int i = 0; i < 32; ++i) {
        printf("x%i\t\t%s\t%i\t\t0x%x\n", i, registerNames[i], (registers + i)->data, (registers + i)->data);
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
