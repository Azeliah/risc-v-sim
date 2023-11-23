#include "memory.h"

unsigned int fetchInstruction(Memory *memory, unsigned int programCounter) {
    unsigned char *firstByte = &memory->startAddress[programCounter];
    unsigned int instruction = 0;
    for (int i = 0; i < 4; ++i) {
        instruction += ((unsigned int) firstByte[i] << i * 8);
    }
    return instruction;
}

void loadData(Memory *memory, unsigned int address) {
    switch (*memory->dataType) {
        case 0x0: // Load byte
            memory->memOutRegister.data =
                    signExtend((unsigned int) memory->startAddress[address], 7);
            break;
        case 0x1: // Load half-word
            memory->memOutRegister.data =
                    signExtend((unsigned int) memory->startAddress[address] +
                               (((unsigned int) memory->startAddress[address]) << 8),
                               15);
            break;
        case 0x2: // Load word
            memory->memOutRegister.data = fetchInstruction(memory, address);
            break;
        case 0x4: // Load byte unsigned
            memory->memOutRegister.data = (unsigned int) memory->startAddress[address];
            break;
        case 0x5: // Load half-word unsigned
            memory->memOutRegister.data = (unsigned int) memory->startAddress[address] +
                                          (((unsigned int) memory->startAddress[address]) << 8);
            break;
        default:
            printf("Invalid load funct3.\n");
    }
}

void saveData(Memory *memory, unsigned int address) {
    switch (*memory->dataType) {
        case 0x2: // Save word
            memory->startAddress[address + 3] = (unsigned char) ((*memory->writeData >> 24) & 0xFF);
            memory->startAddress[address + 2] = (unsigned char) ((*memory->writeData >> 16) & 0xFF);
        case 0x1: // Save half-word
            memory->startAddress[address + 1] = (unsigned char) ((*memory->writeData >> 8) & 0xFF);
        case 0x0: // Save byte
            memory->startAddress[address] = (unsigned char) *memory->writeData & 0xFF;
            break;
        default:
            printf("Invalid save funct3.\n");
    }
}
