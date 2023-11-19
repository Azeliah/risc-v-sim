#ifndef RISC_V_SIM_ADDER_H
#define RISC_V_SIM_ADDER_H

typedef struct Adder {
    unsigned int *input1;
    unsigned int *input2;
    unsigned int output;
} Adder;

void executeAdder(Adder *adder);

#endif //RISC_V_SIM_ADDER_H
