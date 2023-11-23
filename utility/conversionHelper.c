#include "conversionHelper.h"

unsigned int bytesToUInt(unsigned char *firstByte) { // Little-Endian to Big-Endian conversion
    return (unsigned int) ((firstByte[3] << 24) + (firstByte[2] << 16) + (firstByte[1] << 8) + firstByte[0]);
}

void uIntToBytes(unsigned int uInt, unsigned char *destination) { // Big-Endian to Little-Endian conversion
    destination[0] = (unsigned char) uInt & 0x000000FF;
    destination[1] = ((unsigned char) uInt & 0x0000FF00) >> 8;
    destination[2] = ((unsigned char) uInt & 0x00FF0000) >> 16;
    destination[3] = ((unsigned char) uInt & 0xFF000000) >> 24;
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
    return signExtend(((instruction >> 20) &0x1F), 4);
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
