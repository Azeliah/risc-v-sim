#ifndef RISC_V_SIM_ALUCONTROL_H
#define RISC_V_SIM_ALUCONTROL_H

typedef struct AluControl {
    unsigned int *opType;
    unsigned int *opCode;
    unsigned int output;
} AluControl;

#endif //RISC_V_SIM_ALUCONTROL_H
