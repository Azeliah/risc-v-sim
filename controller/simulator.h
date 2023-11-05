#ifndef RISC_V_SIM_SIMULATOR_H
#define RISC_V_SIM_SIMULATOR_H

#include "../model/processor.h"
#include "../model/memory.h"
typedef struct Simulator{
    Processor *processor;
    Memory *memory;
} Simulator;
#endif //RISC_V_SIM_SIMULATOR_H
