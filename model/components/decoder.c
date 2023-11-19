#include "decoder.h"


void decodeInstruction(Decoder *decoder) {
    unsigned int opCode = *decoder->instructionInput & 0x7F;         //opCode is the 7 least significant bits
    unsigned int func3 = (*decoder->instructionInput >> 12) & 0x7;   //func 3 are bits 12-14
    unsigned int func7 = (*decoder->instructionInput >> 25);         //func7 are bits 25-31

    switch (opCode) {
        // opcode: 0b0110111 (U-type: LUI)
        case 0b0110111:
            decoder->opCode = lui;
            break;
            // opcode: 0b0010111 (U-type: AUIPC)
        case 0b0010111:
            decoder->opCode = auipc;
            break;
            // opcode: 0b1101111 (J-type: JAL)
        case 0b1101111:
            decoder->opCode = jal;
            break;
            // opcode: 0b1100111 (I-type: JALR)
        case 0b1100111:
            decoder->opCode = jalr;
            break;
            // opcode: 0b1100011 (B-type: BEQ, BNE, BLT, BGE, BLTU, BGEU)
        case 0b1100011:
            switch (func3) {
                case 0b000:
                    decoder->opCode = beq;
                    break;
                case 0b001:
                    decoder->opCode = bne;
                    break;
                case 0b100:
                    decoder->opCode = blt;
                    break;
                case 0b101:
                    decoder->opCode = bge;
                    break;
                case 0b110:
                    decoder->opCode = bltu;
                    break;
                case 0b111:
                    decoder->opCode = bgeu;
                    break;
                default:
                    decoder->opCode = NOP;
                    fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
                    break;
            }
            break;
            // opcode: 0b0000011 (I-type: LB, LH, LW, LBU, LHU)
        case 0b0000011:
            switch (func3) {
                case 0b000:
                    decoder->opCode = lb;
                    break;
                case 0b001:
                    decoder->opCode = lh;
                    break;
                case 0b010:
                    decoder->opCode = lw;
                    break;
                case 0b100:
                    decoder->opCode = lbu;
                    break;
                case 0b101:
                    decoder->opCode = lhu;
                    break;
                default:
                    decoder->opCode = NOP;
                    fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
                    break;
            }
            break;
            // opcode: 0b0100011 (S-type: SB, SH, SW)
        case 0b0100011:
            switch (func3) {
                case 0b000:
                    decoder->opCode = sb;
                    break;
                case 0b001:
                    decoder->opCode = sh;
                    break;
                case 0b010:
                    decoder->opCode = sw;
                    break;
                default:
                    decoder->opCode = NOP;
                    fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
                    break;
            }
            break;
            // opcode: 0b0010011 (I-type: ADDI, SLTI, SLTIU, XORI, ORI, ANDI)
        case 0b0010011:
            switch (func3) {
                case 0b000:
                    decoder->opCode = addi;
                    break;
                case 0b010:
                    decoder->opCode = slti;
                    break;
                case 0b011:
                    decoder->opCode = sltiu;
                    break;
                case 0b100:
                    decoder->opCode = xori;
                    break;
                case 0b110:
                    decoder->opCode = ori;
                    break;
                case 0b111:
                    decoder->opCode = andi;
                    break;
                case 0b001:
                    decoder->opCode = slli;
                    break;
                case 0b101:
                    switch (func7 &
                            0b1111110) {        // func7 for srli is 000000X and srai is 010000X, hence the &0b1111110
                        case 0b0000000:
                            decoder->opCode = srli;
                            break;
                        case 0b0100000:
                            decoder->opCode = srai;
                            break;
                        default:
                            decoder->opCode = NOP;
                            fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
                            break;
                    }
                    break;
                default:
                    decoder->opCode = NOP;
                    fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
            }
            break;
            // opcode: 0b0110011 (R-type: ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND)
        case 0b0110011:
            switch (func3) {
                case 0b000:
                    switch (func7) {
                        case 0b0000000:
                            decoder->opCode = add;
                            break;
                        case 0b0100000:
                            decoder->opCode = sub;
                            break;
                        default:
                            decoder->opCode = NOP;
                            fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
                            break;
                    }
                    break;
                case 0b001:
                    decoder->opCode = sll;
                    break;
                case 0b010:
                    decoder->opCode = slt;
                    break;
                case 0b011:
                    decoder->opCode = sltu;
                    break;
                case 0b100:
                    decoder->opCode = xor;
                    break;
                case 0b101:
                    switch (func7) {
                        case 0b0000000:
                            decoder->opCode = srl;
                            break;
                        case 0b0100000:
                            decoder->opCode = sra;
                            break;
                        default:
                            decoder->opCode = NOP;
                            fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
                            break;
                    }
                    break;
                case 0b110:
                    decoder->opCode = or;
                    break;
                case 0b111:
                    decoder->opCode = and;
                    break;
                default:
                    decoder->opCode = NOP;
                    fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
                    break;
            }
            break;
        default:
            decoder->opCode = NOP;
            fprintf(stderr, "unknown instruction: %x", *decoder->instructionInput);
            break;
    }
}