#ifndef RISC_V_SIM_CONTROL_H
#define RISC_V_SIM_CONTROL_H

typedef struct Control {
    unsigned int *input;
    unsigned int branch;
    unsigned int memRead;
    unsigned int memToReg;
    unsigned int aluOp;
    unsigned int memWrite;
    unsigned int aluSource;
    unsigned int registerWrite;
} Control;
#endif //RISC_V_SIM_CONTROL_H
