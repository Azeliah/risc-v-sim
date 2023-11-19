#ifndef RISC_V_SIM_MULTIPLEXER_H
#define RISC_V_SIM_MULTIPLEXER_H

typedef struct Multiplexer {
    unsigned int *input1;
    unsigned int *input2;
    unsigned int *signal;
    unsigned int output;
} Multiplexer;

void selectOutput(Multiplexer *multiplexer);

#endif //RISC_V_SIM_MULTIPLEXER_H
