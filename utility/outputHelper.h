#ifndef RISC_V_SIM_OUTPUTHELPER_H
#define RISC_V_SIM_OUTPUTHELPER_H

#include <malloc.h>
#include <stdio.h>

#include "../model/components/register.h"
#include "../model/memory.h"
#include "conversionHelper.h"

void printRegistersConvention(Register *registers);

void printRegistersAssessment(Register *registers);

void postInstruction(unsigned int instruction);

#endif //RISC_V_SIM_OUTPUTHELPER_H
