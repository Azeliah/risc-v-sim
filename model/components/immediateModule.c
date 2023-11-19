#include "immediateModule.h"

unsigned int signExtend(unsigned int num, int mostSignificant) {
    unsigned int sign = (1 << mostSignificant) & num;
    if (sign) {
        return num | (0xFFFFFFFF << (mostSignificant + 1));
    } else return num;
}

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
            immediateModule->output = signExtend((instruction & 0xFFF00000) >> 20, 11);
            break;
        case 0x17:
        case 0x37:
            // U-type: [31:12] => [31:12]
            immediateModule->output = (instruction & 0xFFFFF000);
            break;
        case 0x23:
            // S-type: [31:25] [11:7] => [11:5] [4:0]
            immediateModule->output = signExtend(((instruction & 0xFE000000) >> 20) +
                                                 ((instruction & 0x00000F80) >> 5),
                                                 11);
            break;
        case 0x63:
            // SB-type: [31] [7] [30:25] [11:8] => [12] [11] [10:5] [4:1]
            immediateModule->output = signExtend(((instruction & 0x80000000) >> 19) +
                                                 ((instruction & 0x00000080) << 4) +
                                                 ((instruction & 0x7C000000) >> 20) +
                                                 ((instruction & 0x00000F00) >> 7),
                                                 11);
            break;
        case 0x6F:
            // UJ-type: [31] [30:21] [20] [19:12] => [20] [10:1] [11] [19:12]
            immediateModule->output = signExtend(((instruction & 0x80000000) >> 11) +
                                                 ((instruction & 0x7FE00000) >> 20) +
                                                 ((instruction & 0x00100000) >> 9) +
                                                 ((instruction & 0x000FF000)),
                                                 12);
            break;
        default:
            break;
    }
}
