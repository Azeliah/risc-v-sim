#ifndef RISC_V_SIM_ALUCONTROL_H
#define RISC_V_SIM_ALUCONTROL_H

typedef struct AluControl {
    unsigned int *opType; // aluOp from control
    unsigned int *funct3; // From decoder
    unsigned int *bit30; // From decoder
    unsigned int output;
} AluControl;

#endif //RISC_V_SIM_ALUCONTROL_H
