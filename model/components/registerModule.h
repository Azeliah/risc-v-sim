#ifndef RISC_V_SIM_REGISTER_MODULE_H
#define RISC_V_SIM_REGISTER_MODULE_H

#include "register.h"

typedef struct RegisterModule {
    Register registers[32];
    unsigned int output1;
    unsigned int output2;
    unsigned int *register1; // r1 from decoder
    unsigned int *register2; // r2 from decoder
    unsigned int *writeRegister; // writeRegister from decoder
    unsigned int *writeSignal; // RegWrite from control
} RegisterModule;

void selectRegisters(RegisterModule *registerModule);
void writeToRegister(RegisterModule *registerModule, unsigned int value);

#endif //RISC_V_SIM_REGISTER_MODULE_H
