#ifndef RISC_V_SIM_MEMORY_H
#define RISC_V_SIM_MEMORY_H

#include "components/register.h"

typedef struct Memory {
    unsigned int size;
    Register memOutRegister;
    unsigned int *writeSignal;
    unsigned int *writeData;
    unsigned int *dataType;
    unsigned char *startAddress; // For byte addressable memory.
} Memory;

#endif //RISC_V_SIM_MEMORY_H
