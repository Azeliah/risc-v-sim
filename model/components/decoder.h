#ifndef RISC_V_SIM_DECODER_H
#define RISC_V_SIM_DECODER_H

#include <stdio.h>

enum opCodeSignal {
    lui, auipc, jal, jalr, beq, bne, blt, bge, bltu, bgeu, lb, lh, lw, lbu, lhu, sb, sh, sw,
    addi, slti, sltiu, xori, ori, andi, slli, srli, srai, add, sub, sll, slt, sltu, xor, srl,
    sra, or, and, NOP
};

typedef struct Decoder {
    unsigned int *instructionInput;
    enum opCodeSignal opCode;
    unsigned int r1Address;
    unsigned int r2Address;
    unsigned int rwAddress;
    unsigned int immediateBits;
    unsigned int funct3;
    unsigned int bit30;
} Decoder;


void decodeInstruction(Decoder *decoder);

#endif //RISC_V_SIM_DECODER_H
