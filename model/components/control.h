#ifndef RISC_V_SIM_CONTROL_H
#define RISC_V_SIM_CONTROL_H

#include <stdio.h>

typedef struct Control {
    unsigned int *input;
    unsigned int branch;
    unsigned int memRead;
    unsigned int memToReg;
    unsigned int aluOp;
    unsigned int memWrite;
    unsigned int aluSource;
    unsigned int registerWrite;
    unsigned int jal;
    unsigned int jalr;
    unsigned int ecall;
} Control;

void updateControlSignals(Control *control);

#endif //RISC_V_SIM_CONTROL_H
