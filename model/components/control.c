#include "control.h"

void updateControlSignals(Control *control) {
    control->memWrite = 0;
    control->memRead = 0;
    control->memToReg = 0;
    control->branch = 0;
    control->aluSource = 0;
    control->aluOp = 0; // 0b00(0) when add, 0b01(1) when subtract, 0b10(2) when func3/7 decides
    control->registerWrite = 0;

    switch (*control->input) {
        case 0x03: // Load instructions
            control->aluSource = 1;
            control->memToReg = 1;
            control->registerWrite = 1;
            control->memRead = 1;
            break;
        case 0x0F: // Fence instructions
            // Not implemented
            break;
        case 0x13: // Immediate arithmetic instructions
            control->aluSource = 1;
            control->registerWrite = 1;
            control->aluOp = 0b10;
            break;
        case 0x17: // Add upper immediate to program counter
            control->branch = 1;
            break;
        case 0x23: // Save instructions
            control->aluSource = 1;
            control->memWrite = 1;
            break;
        case 0x33: // Register arithmetic instructions
            control->registerWrite = 1;
            control->aluOp = 0b10;
            break;
        case 0x37: // Load upper immediate
            control->aluSource = 1;
            control->registerWrite = 1;
            break;
        case 0x63: // Branch instructions
            control->branch = 1;
            control->aluOp = 0b10;
            break;
        case 0x67: // Jump and link register
            control->aluSource = 1;
            control->branch = 1;
            control->registerWrite = 1;
            // FIXME
            break;
        case 0x6F: // Jump and link
            control->aluSource = 1;
            control->branch = 1;
            control->registerWrite = 1;
            // FIXME
            break;
        case 0x73: // ecall, ebreak and CSRR.
            // FIXME exit?
            break;
        default:
            printf("Invalid opcode: %x\n", *control->input);
    }
}
