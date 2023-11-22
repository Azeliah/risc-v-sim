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

typedef struct Simulator {
    Processor *processor;
    Memory *memory;
    Multiplexer *memoryMux;
    Multiplexer *pcMux;
    Adder *pcAdd4;
    Adder *pcAddImm;
    unsigned int postInstruction;
    unsigned int pcIncrement;
    unsigned int programCounter;
    unsigned int instruction;
} Simulator;

void initialize(Simulator *simulator, int memorySize);

void tearDown(Simulator *simulator);

void reset(Simulator *simulator);

void loadProgram(Simulator *simulator, char *path);

void run(Simulator *simulator);

unsigned int runCycle(Simulator *simulator);

#endif //RISC_V_SIM_SIMULATOR_H
