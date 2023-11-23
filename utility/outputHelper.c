#include "outputHelper.h"

void printRegisters(Register *registers) {
    char *registerNames[] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1",
                             "t2", "s0/fp", "s1", "a0", "a1", "a2", "a3",
                             "a4", "a5", "a6", "a7", "s2", "s3", "s4",
                             "s5", "s6", "s7", "s8", "s9", "s10", "s11",
                             "t3", "t4", "t5", "t6"};
    printf("Register\tName\t\tDecimal\t\tHexadecimal\n");
    for (int i = 0; i < 32; ++i) {
        printf("x%i\t\t%s\t\t%i\t\t0x%x\n", i, registerNames[i], (registers + i)->data, (registers + i)->data);
    }
}

char *toBinary(unsigned int num) {
    char *result = malloc(sizeof(char) * 36);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            *(result + 9 * i + j) = (num << (8 * i + j)) & 0x80000000 ? '1' : '0';
        }
        *(result + 9 * (i + 1) - 1) = ' ';
    }
    *(result + 35) = '\0';
    return result;
}

void printMemoryDataBytesReversed(unsigned int num) {
    unsigned int reversed = ((num & 0xFF000000) >> 24) + ((num & 0x00FF0000) >> 8) +
                            ((num & 0x0000FF00) << 8) + ((num & 0x000000FF) << 24);
    char *binary = toBinary(reversed);
    printf("Written to memory (reversed): 0x%x; Binary: %s\n", reversed, binary);
    free(binary);
}

void printMemoryData(unsigned int num) {
    char *binary = toBinary(num);
    printf("Written to memory: 0x%x; Binary: %s\n", num, binary);
    free(binary);
}

void printMemory(Memory *memory) { // If there exists a 0 in the program, this will terminate prematurely.
    unsigned char *ptr = memory->startAddress;
    while (*ptr) {
        printMemoryData(*ptr++);
    }
}

// FIXME: This entire file doesn't work properly after memory change from ints to chars.
void printMemoryBytesReversed(Memory *memory) {
    unsigned char *ptr = memory->startAddress;
    while (*ptr) {
        printMemoryDataBytesReversed(*ptr++);
    }
}

void postInstruction(unsigned int instruction) {
    /*
     *  R type:  [31:25]: funct7, [24:20]: SR2, [19:15]: SR1, [14:12]: funct3, [11:7]: DR, [6:0]: opcode.
     *
     *  I type:  [31:20]: imm [11:0], [19:15]: SR1, [14:12]: funct3, [11:7]: DR, [6:0]: opcode.
     *
     *  S type:  [31:25]: imm [11:5], [24:20]: SR2, [19:15]: SR1, [14:12]: funct3, [11:7]: imm [4:0], [6:0]: opcode.
     *
     *  SB type: [31]: imm [12], [30:25]: imm [10:5], [24:20]: SR2, [19:15]: SR1, [14:12]: funct3, [11:8]: imm [4:1], [7]: imm [11], [6:0]: opcode.
     *
     *  U type:  [31:12]: imm [31:12], [11:7]: DR, [6:0]: opcode.
     *
     *  UJ type: [31]: imm [20], [30:21]: imm [10:1], [20]: imm [11], [19:12]: imm [19:12], [11:7]: DR, [6:0]: opcode.
     */
    enum opType {
        i, u, s, r, sb, uj
    };
    char *registerNames[] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1",
                             "t2", "s0/fp", "s1", "a0", "a1", "a2", "a3",
                             "a4", "a5", "a6", "a7", "s2", "s3", "s4",
                             "s5", "s6", "s7", "s8", "s9", "s10", "s11",
                             "t3", "t4", "t5", "t6"};
    unsigned int opcode = instruction & 0x7F;
    unsigned int funct3 = (instruction >> 12) & 0x7;
    unsigned int bit30 = (instruction >> 30) & 0x1;
    char *operation;
    int immediate;
    unsigned int sr1 = (instruction >> 15) & 0x1F;
    unsigned int sr2 = (instruction >> 20) & 0x1F;
    unsigned int dr = (instruction >> 7) & 0x1F;
    enum opType opType;
    switch (opcode) {
        case 0x03: // I type
            opType = i;
            switch (funct3) {
                case 0x0:
                    operation = "lb";
                    break;
                case 0x1:
                    operation = "lh";
                    break;
                case 0x2:
                    operation = "lw";
                    break;
                case 0x4:
                    operation = "lhu";
                    break;
                case 0x5:
                    operation = "lbu";
                    break;
                default:
                    printf("Unknown load instruction: %x\n", instruction);
                    return;

            }
            immediate = (int) getImmediateI(instruction);
            break;
        case 0x0F: // Fence - not in use.
            printf("Fence instruction, not in use.\n");
            return;
        case 0x13: // I type
            opType = i;
            switch (funct3) {
                case 0x0:
                    operation = "addi";
                    break;
                case 0x1:
                    operation = "slli";
                    break;
                case 0x2:
                    operation = "slti";
                    break;
                case 0x3:
                    operation = "sltiu";
                    break;
                case 0x4:
                    operation = "xori";
                    break;
                case 0x5:
                    if (bit30) operation = "srai";
                    else operation = "srli";
                    break;
                case 0x6:
                    operation = "ori";
                    break;
                case 0x7:
                    operation = "andi";
                    break;
                default:
                    printf("Unknown immediate arithmetic instruction: %x\n", instruction);
                    return;
            }
            if (funct3 == 0x5) {
                immediate = (int) getImmediateIShift(instruction);
            } else {
                immediate = (int) getImmediateI(instruction);
            }
            break;
        case 0x17: // U type
            opType = u;
            operation = "auipc";
            immediate = (int) getImmediateU(instruction);
            break;
        case 0x23: // S type
            opType = s;
            switch (funct3) {
                case 0x0:
                    operation = "sb";
                    break;
                case 0x1:
                    operation = "sh";
                    break;
                case 0x2:
                    operation = "sw";
                    break;
                default:
                    printf("Unknown save instruction: %x\n", instruction);
                    return;
            }
            immediate = (int) getImmediateS(instruction);
            break;
        case 0x33: // R type, no imm
            opType = r;
            switch (funct3) {
                case 0x0:
                    if (bit30) operation = "add";
                    else operation = "sub";
                    break;
                case 0x1:
                    operation = "sll";
                    break;
                case 0x2:
                    operation = "slt";
                    break;
                case 0x3:
                    operation = "sltu";
                    break;
                case 0x4:
                    operation = "xor";
                    break;
                case 0x5:
                    if (bit30) operation = "sra";
                    else operation = "srl";
                    break;
                case 0x6:
                    operation = "or";
                    break;
                case 0x7:
                    operation = "and";
                    break;
                default:
                    printf("Unknown register arithmetic instruction: %x\n", instruction);
                    return;
            }
            break;
        case 0x37: // U type
            opType = u;
            operation = "lui";
            immediate = (int) getImmediateU(instruction);
            break;
        case 0x63: // SB type
            opType = sb;
            switch (funct3) {
                case 0x0:
                    operation = "beq";
                    break;
                case 0x1:
                    operation = "bne";
                    break;
                case 0x4:
                    operation = "blt";
                    break;
                case 0x5:
                    operation = "bge";
                    break;
                case 0x6:
                    operation = "bltu";
                    break;
                case 0x7:
                    operation = "bgeu";
                    break;
                default:
                    printf("Unknown branch instruction: %x\n", instruction);
                    return;
            }
            immediate = (int) getImmediateSB(instruction);
            break;
        case 0x67: // I type
            opType = i;
            switch (funct3) {
                case 0x0:
                    operation = "jalr";
                    break;
                default:
                    printf("Unknown jalr instruction: %x\n", instruction);
                    return;
            }
            immediate = (int) getImmediateI(instruction);
            break;
        case 0x6F: // UJ type
            opType = uj;
            operation = "jal";
            immediate = (int) getImmediateUJ(instruction);
            break;
        case 0x73: // I type
            opType = i;
            immediate = (int) getImmediateI(instruction);
            if (funct3 == 0x0) {
                if (immediate == 0x1) operation = "ebreak";
                else if (immediate == 0x0) operation = "ecall";
                else {
                    printf("Unknown system call instruction: %x\n", instruction);
                    return;
                }
                break;
            } else {
                printf("Unknown CSRR instruction: %x\n", instruction);
                return;
            }
        default:
            printf("Unknown instruction: %x\n", instruction);
            return;
    }
    switch (opType) {
        case i:
            printf("%s %s, %s, %d\t(0x%x)\n", operation, registerNames[dr], registerNames[sr1], immediate, immediate);
            break;
        case u:
            printf("%s %s, %d\t(0x%x)\n", operation, registerNames[dr], immediate, immediate);
            break;
        case s:
            printf("%s %s, %s, %d\t(0x%x)\n", operation, registerNames[sr1], registerNames[sr2], immediate, immediate);
            break;
        case r:
            printf("%s %s, %s, %s\n", operation, registerNames[dr], registerNames[sr1], registerNames[sr2]);
            break;
        case sb:
            printf("%s %s, %s, %d\t(0x%x)\n", operation, registerNames[sr1], registerNames[sr2], immediate, immediate);
            break;
        case uj:
            printf("%s %s, %d\t(0x%x)\n", operation, registerNames[dr], immediate, immediate);
            break;
        default:
            printf("No.\n");
    }
}
