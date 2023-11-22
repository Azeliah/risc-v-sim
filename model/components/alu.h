#ifndef RISC_V_SIM_ALU_H
#define RISC_V_SIM_ALU_H

#include "register.h"
#include "aluControl.h"

typedef struct Alu {
    unsigned int *input1;
    unsigned int *input2;
    unsigned int *branchControl;
    enum aluCtrlToAluSignal *op;
    unsigned int branchSignal;
    unsigned int output;
} Alu;

void doOperation(Alu *alu);

void addition(Alu *alu);

void subtraction(Alu *alu);

void logicalAnd(Alu *alu);

void logicalOr(Alu *alu);

void logicalXor(Alu *alu);

void shiftLeft(Alu *alu);

void shiftRightLogical(Alu *alu);

void shiftRightArithmetic(Alu *alu);

void setLessThan(Alu *alu);

void setLessThanU(Alu *alu);

void branchEquals(Alu *alu);

void branchNotEquals(Alu *alu);

void branchLessThan(Alu *alu);

void branchGreaterEquals(Alu *alu);

void branchLessThanU(Alu *alu);

void branchGreaterEqualsU(Alu *alu);

int convertToSigned(unsigned int num);

#endif //RISC_V_SIM_ALU_H
