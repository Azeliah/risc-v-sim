#include "alu.h"

void doOperation(Alu *alu) {
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
        case sl:
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
}

void subtraction(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void logicalAnd(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void logicalOr(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void logicalXor(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void shiftLeft(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void shiftRightLogical(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void shiftRightArithmetic(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void setLessThan(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void setLessThanU(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void branchEquals(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void branchNotEquals(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void branchLessThan(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void branchGreaterEquals(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void branchLessThanU(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}

void branchGreaterEqualsU(Alu *alu) {
    alu->output = *alu->input1 + *alu->input2;
}
