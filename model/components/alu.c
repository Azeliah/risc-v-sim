#include "alu.h"

void doOperation(Alu *alu) {
    alu->branchSignal = 0;
    switch (*alu->op) {
        case add:
            addition(alu);
            break;
        case sub:
            subtraction(alu);
            break;
        case and:
            logicalAnd(alu);
            break;
        case or:
            logicalOr(alu);
            break;
        case xor:
            logicalXor(alu);
            break;
        case sll:
            shiftLeft(alu);
            break;
        case srl:
            shiftRightLogical(alu);
            break;
        case sra:
            shiftRightArithmetic(alu);
            break;
        case slt:
            setLessThan(alu);
            break;
        case sltu:
            setLessThanU(alu);
            break;
        case beq:
            branchEquals(alu);
            break;
        case bne:
            branchNotEquals(alu);
            break;
        case blt:
            branchLessThan(alu);
            break;
        case bge:
            branchGreaterEquals(alu);
            break;
        case bltu:
            branchLessThanU(alu);
            break;
        case bgeu:
            branchGreaterEqualsU(alu);
            break;
    }
}

void addition(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
    alu->branchSignal = *alu->branchControl;
}

void subtraction(Alu *alu) {
    alu->output = *alu->input1 - *alu->input2;
}

void logicalAnd(Alu *alu) {
    alu->output = *alu->input1 & *alu->input2;
}

void logicalOr(Alu *alu) {
    alu->output = *alu->input1 | *alu->input2;
}

void logicalXor(Alu *alu) {
    alu->output = *alu->input1 ^ *alu->input2;
}

void shiftLeft(Alu *alu) {
    alu->output = *alu->input1 << *alu->input2;
}

void shiftRightLogical(Alu *alu) {
    alu->output = *alu->input1 >> *alu->input2;
}

void shiftRightArithmetic(Alu *alu) {
    if (*alu->input1 & (1 << 31)) { // Negative in 2's complement
        if (*alu->input2 > 31) {
            alu->output = 0xFFFFFFFF;
        } else {
            unsigned int bitsRemaining = 32 - *alu->input2;
            alu->output = (*alu->input1 >> *alu->input2) + (0xFFFFFFFF << bitsRemaining);
        }
    } else {
        alu->output = *alu->input1 >> *alu->input2;
    }
}

void setLessThan(Alu *alu) {
    alu->output = (convertToSigned(*alu->input1) < convertToSigned(*alu->input2)) ? 1 : 0;
}

void setLessThanU(Alu *alu) {
    alu->output = (*alu->input1 < *alu->input2) ? 1 : 0;
}

void branchEquals(Alu *alu) {
    alu->output = *alu->input1 - *alu->input2;
    if (alu->output == 0) alu->branchSignal = 1;
}

void branchNotEquals(Alu *alu) {
    alu->output = *alu->input1 - *alu->input2;
    if (alu->output != 0) alu->branchSignal = 1;
}

void branchLessThan(Alu *alu) {
    alu->output = *alu->input1 - *alu->input2;
    if (convertToSigned(*alu->input1) < convertToSigned(*alu->input2)) alu->branchSignal = 1;
}

void branchGreaterEquals(Alu *alu) {
    alu->output = *alu->input2 - *alu->input1;
    if (convertToSigned(*alu->input1) >= convertToSigned(*alu->input2)) alu->branchSignal = 1;
}

void branchLessThanU(Alu *alu) {
    alu->output = *alu->input1 - *alu->input2;
    if (*alu->input1 < *alu->input2) alu->branchSignal = 1;
}

void branchGreaterEqualsU(Alu *alu) {
    alu->output = *alu->input2 - *alu->input1;
    if (*alu->input1 >= *alu->input2) alu->branchSignal = 1;
}

int convertToSigned(unsigned int num) {
    if (num & (1 << 31)) {
        return (int) (num & 0x7FFFFFFF) - (1 << 31);
    } else {
        return (int) num;
    }
}
