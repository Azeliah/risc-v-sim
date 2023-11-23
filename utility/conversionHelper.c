#include "conversionHelper.h"

unsigned int toLittleEndian(unsigned int num) {
    return ((num & 0xFF) << 24) + ((num & 0xFF00) << 8) + ((num & 0xFF0000) >> 8) + ((num & 0xFF000000) >> 24);
}

unsigned int signExtend(unsigned int num, int mostSignificant) {
    unsigned int sign = (1 << mostSignificant) & num;
    if (sign) {
        return num | (0xFFFFFFFF << (mostSignificant + 1));
    } else return num;
}

unsigned int getImmediateI(unsigned int instruction) {
    return signExtend(((instruction >> 20) & 0xFFF), 11);
}

unsigned int getImmediateIShift(unsigned int instruction) {
    return ((instruction >> 20) & 0x1F);
}

unsigned int getImmediateU(unsigned int instruction) {
    return (instruction & 0xFFFFF000);
}

unsigned int getImmediateS(unsigned int instruction) {
    return signExtend(((instruction >> 20) & 0xFE0) +
                      ((instruction >> 7) & 0x1F),
                      11);
}

unsigned int getImmediateSB(unsigned int instruction) {
    return signExtend(((instruction & 0x80000000) >> 19) +
                      ((instruction & 0x7E000000) >> 20) +
                      ((instruction & 0xF00) >> 7) +
                      ((instruction & 0x80) << 4),
                      12);
}

unsigned int getImmediateUJ(unsigned int instruction) {
    return signExtend(((instruction >> 11) & 0x100000) +
                      ((instruction >> 20) & 0x7FE) +
                      ((instruction >> 9) & 0x800) +
                      (instruction & 0xFF000),
                      20);
}
