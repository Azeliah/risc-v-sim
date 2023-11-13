#ifndef RISC_V_SIM_DECODER_H
#define RISC_V_SIM_DECODER_H

typedef struct Decoder {
    int instructionInput;
    int opCode;
    int r1Address;
    int r2Address;
    int writeRegister;
} Decoder;
#endif //RISC_V_SIM_DECODER_H
