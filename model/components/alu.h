#ifndef RISC_V_SIM_ALU_H
#define RISC_V_SIM_ALU_H

#include "register.h"

typedef struct Alu {
    unsigned int *input1;
    unsigned int *input2;
    unsigned int *branchControl;
    unsigned int *op;
    unsigned int branchSignal;
    unsigned int output;
} Alu;

void doOperation(Alu *alu);

#endif //RISC_V_SIM_ALU_H
