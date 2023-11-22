#include "immediateModule.h"

void generateImmediate(ImmediateModule *immediateModule) {
    immediateModule->output = 0;
    unsigned int instruction = *immediateModule->input;
    unsigned int opcode = instruction & 0x7F;
    switch (opcode) {
        case 0x03:
        case 0x0F:
        case 0x13:
        case 0x67:
        case 0x73:
            // I-type: [31:20] => [11:0]
            immediateModule->output = getImmediateI(instruction);
            break;
        case 0x17:
        case 0x37:
            // U-type: [31:12] => [31:12]
            immediateModule->output = getImmediateU(instruction);
            break;
        case 0x23:
            // S-type: [31:25] [11:7] => [11:5] [4:0]
            immediateModule->output = getImmediateS(instruction);
            break;
        case 0x63:
            // SB-type: [31] [7] [30:25] [11:8] => [12] [11] [10:5] [4:1]

            immediateModule->output = getImmediateSB(instruction);
            break;
        case 0x6F:
            // UJ-type: [31] [30:21] [20] [19:12] => [20] [10:1] [11] [19:12]
            immediateModule->output = getImmediateUJ(instruction);
            break;
        default:
            break;
    }
}
