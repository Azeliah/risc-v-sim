#ifndef RISC_V_SIM_ALUCONTROL_H
#define RISC_V_SIM_ALUCONTROL_H


enum aluCtrlToAluSignal {
    add, sub, and, or, xor, sll, srl, sra, slt, sltu, beq, bne, blt, bge, bltu, bgeu
};

typedef struct AluControl {
    unsigned int *opType; // aluOp from control
    unsigned int *func3; // From decoder
    unsigned int *bit30; // From decoder
    unsigned int *branch; // From control
    enum aluCtrlToAluSignal output;
} AluControl;

void updateAluControlSignal(AluControl *aluControl);

#endif //RISC_V_SIM_ALUCONTROL_H
