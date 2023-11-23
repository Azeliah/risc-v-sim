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
    return signExtend(((instruction >> 20) & 0x1F), 4);
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
    return signExtend(((instruction >> 19) & 0x1000) +
                      ((instruction >> 20) & 0xFE0) +
                      ((instruction >> 7) & 0x1E) +
                      ((instruction << 4) & 0x800),
                      12);
}

unsigned int getImmediateUJ(unsigned int instruction) {
    return signExtend(((instruction >> 11) & 0x100000) +
                      ((instruction >> 20) & 0x7FE) +
                      ((instruction >> 9) & 0x800) +
                      (instruction & 0xFF000),
                      20);
}
