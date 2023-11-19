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
