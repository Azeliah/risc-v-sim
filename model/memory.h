#ifndef RISC_V_SIM_MEMORY_H
#define RISC_V_SIM_MEMORY_H

#include <stdio.h>

#include "components/register.h"
#include "../utility/conversionHelper.h"

typedef struct Memory {
    unsigned int size;
    Register memOutRegister;
    unsigned int *writeSignal;
    unsigned int *writeData;
    unsigned int *dataType;
    unsigned char *startAddress; // For byte addressable memory.
} Memory;

unsigned int fetchInstruction(Memory *memory, unsigned int programCounter);

void loadData (Memory *memory, unsigned int address);

void saveData(Memory *memory, unsigned int address);

#endif //RISC_V_SIM_MEMORY_H
