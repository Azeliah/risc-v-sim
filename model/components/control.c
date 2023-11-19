#include "control.h"

void updateControlSignals(Control *control) {
    control->memWrite = 0;
    control->memRead = 0;
    control->memToReg = 0;
    control->branch = 0;
    control->aluSource = 0;
    control->aluOp = 0;
    control->registerWrite = 0;
    // TODO: Less giant switch case
    switch (*control->input) {
        case 0x03: // Load instructions
            break;
        case 0x0F: // Fence instructions
            break;
        case 0x13: // Immediate arithmetic instructions
            break;
        case 0x17: // Add upper immediate to program counter
            break;
        case 0x23: // Save instructions
            break;
        case 0x33: // Register arithmetic instructions
            break;
        case 0x37: // Load upper immediate
            break;
        case 0x63: // Branch instructions
            break;
        case 0x67: // Jump and link register
            break;
        case 0x6F: // Jump and link
            break;
        case 0x73: // ecall, ebreak and CSRR.
            break;
        default:
            printf("Invalid opcode: %x\n", *control->input);
    }
}
