#ifndef RISC_V_SIM_CONTROL_H
#define RISC_V_SIM_CONTROL_H

typedef struct Control {
    int branch;
    int memRead;
    int memToReg;
    int aluOp;
    int memWrite;
    int aluSource;
    int registerWrite;
} Control;
#endif //RISC_V_SIM_CONTROL_H
