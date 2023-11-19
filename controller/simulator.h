#ifndef RISC_V_SIM_SIMULATOR_H
#define RISC_V_SIM_SIMULATOR_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../model/processor.h"
#include "../model/memory.h"
#include "../utility/byteHelper.h"
#include "../utility/outputHelper.h"

typedef struct Simulator {
    Processor *processor;
    Memory *memory;
    unsigned int programCounter;
    unsigned int instruction;
} Simulator;

void initialize(Simulator *simulator, int memorySize);

void tearDown(Simulator *simulator);

void runTests(Simulator *simulator);

void reset(Simulator *simulator);

void loadProgram(Simulator *simulator, char *path);

void run(Simulator *simulator);

int runCycle(Simulator *simulator);

#endif //RISC_V_SIM_SIMULATOR_H
