#ifndef RISC_V_SIM_ALU_H
#define RISC_V_SIM_ALU_H

#include "register.h"

typedef struct Alu {
    Register *input1;
    Register *input2;
    Register *output;
} Alu;


#endif //RISC_V_SIM_ALU_H
