#include <stdio.h>
#include "aluControl.h"

void updateAluControlSignal(AluControl *aluControl) {
    unsigned int funct3_and_7 =
            (*aluControl->funct3) + ((*aluControl->bit30) << 3); // bit 30 as 3rd bit, and funct3 as bit 0,1 and 2
    switch (*aluControl->opType) {
        case 0b00: // case opType = add
            aluControl->output = add;
            break;
        case 0b01:
            // intentionally left blank
            break;
        case 0b10: // case opType = func types
            switch (*aluControl->branch) {
                case 0: // case not branching
                    switch (funct3_and_7) {
                        case 0b0000:
                            aluControl->output = add;
                            break;
                        case 0b1000: // case subtract
                            aluControl->output = sub;
                            break;
                        case 0b0111:
                            aluControl->output = and;
                            break;
                        case 0b0110:
                            aluControl->output = or;
                            break;
                        case 0b0100:
                            aluControl->output = xor;
                            break;
                        case 0b0001:
                            aluControl->output = sll;
                            break;
                        case 0b0101:
                            aluControl->output = srl;
                            break;
                        case 0b1101:
                            aluControl->output = sra;
                            break;
                        case 0b0010:
                            aluControl->output = slt;
                            break;
                        case 0b0011:
                            aluControl->output = sltu;
                            break;
                        default:
                            printf("wrong funct3/7???? should not be able to run");
                            break;
                    }
                    break;
                case 1: // case branching
                    switch (*aluControl->funct3) {
                        case 0b000:
                            aluControl->output = beq;
                            break;
                        case 0b001:
                            aluControl->output = bne;
                            break;
                        case 0b100:
                            aluControl->output = blt;
                            break;
                        case 0b101:
                            aluControl->output = bge;
                            break;
                        case 0b110:
                            aluControl->output = bltu;
                            break;
                        case 0b111:
                            aluControl->output = bgeu;
                            break;
                        default:
                            printf("Unknown funct3 in aluControl - should not be able to run -.-");
                            break;
                    }
                    break;
            }
            break;
        case 0b11:
            switch (*aluControl->funct3) {
                case 0b000:
                    aluControl->output = add;
                    break;
                case 0b111:
                    aluControl->output = and;
                    break;
                case 0b110:
                    aluControl->output = or;
                    break;
                case 0b100:
                    aluControl->output = xor;
                    break;
                case 0b001:
                    aluControl->output = sll;
                    break;
                case 0b101:
                    if (*aluControl->bit30) aluControl->output = sra;
                    else aluControl->output = srl;
                    break;
                case 0b010:
                    aluControl->output = slt;
                    break;
                case 0b011:
                    aluControl->output = sltu;
                    break;
                default:
                    printf("wrong funct3/7???? should not be able to run");
                    break;
            }
        default:
            break;
    }
}
