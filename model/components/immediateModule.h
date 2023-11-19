#ifndef RISC_V_SIM_IMMEDIATEMODULE_H
#define RISC_V_SIM_IMMEDIATEMODULE_H

typedef struct ImmediateModule {
    unsigned int *input;
    unsigned int output;
} ImmediateModule;

void generateImmediate(ImmediateModule *immediateModule);

#endif //RISC_V_SIM_IMMEDIATEMODULE_H