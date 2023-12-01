#ifndef RISC_V_SIM_SIMULATOR_H
#define RISC_V_SIM_SIMULATOR_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../model/processor.h"
#include "../model/memory.h"
#include "../utility/conversionHelper.h"
#include "../utility/outputHelper.h"
#include "../model/components/adder.h"

enum simulatorStatus {
    running, ecallExit, zeroInstruction
};

typedef struct Simulator {
    Processor *processor;
    Memory *memory;
    Multiplexer *memoryMux;
    Multiplexer *pcMux;
    Multiplexer *jalrMux;
    Adder *pcAdd4;
    Adder *pcAddImm;
    unsigned int *ecallSignal;
    unsigned int *ecallType;
    unsigned int postInstruction;
    unsigned int pcIncrement;
    unsigned int programCounter;
    unsigned int instruction;
    enum simulatorStatus simulatorStatus;
} Simulator;

void initialize(Simulator *simulator, int memorySize);

void tearDown(Simulator *simulator);

void reset(Simulator *simulator);

void loadProgram(Simulator *simulator, char *path);

void run(Simulator *simulator);

void runCycle(Simulator *simulator);

void handleEcall(Simulator *simulator);

#endif //RISC_V_SIM_SIMULATOR_H
