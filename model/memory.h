#ifndef RISC_V_SIM_MEMORY_H
#define RISC_V_SIM_MEMORY_H

typedef struct Memory {
    int size;
    unsigned char *startAddress; // For byte addressable memory.
} Memory;

#endif //RISC_V_SIM_MEMORY_H
