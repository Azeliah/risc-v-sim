#ifndef RISC_V_SIM_DECODER_H
#define RISC_V_SIM_DECODER_H

#include <stdio.h>

typedef struct Decoder {
    unsigned int *instructionInput;
    unsigned int opcode;
    unsigned int r1Address;
    unsigned int r2Address;
    unsigned int rwAddress;
    unsigned int immediateBits;
    unsigned int funct3;
    unsigned int bit30;
} Decoder;

void decodeInstruction(Decoder *decoder);

#endif //RISC_V_SIM_DECODER_H
