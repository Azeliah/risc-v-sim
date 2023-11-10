#ifndef RISC_V_SIM_OUTPUTHELPER_H
#define RISC_V_SIM_OUTPUTHELPER_H

#include <malloc.h>
#include <stdio.h>

#include "../model/components/register.h"
#include "../model/memory.h"

void printRegisters(Register *registers);

char *toBinary(unsigned int num);

void printMemoryData(unsigned int num);

void printMemoryDataBytesReversed(unsigned int num);

void printMemory(Memory *memory);

void printMemoryBytesReversed(Memory *memory);

#endif //RISC_V_SIM_OUTPUTHELPER_H