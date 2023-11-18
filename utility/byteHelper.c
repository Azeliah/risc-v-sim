#include "byteHelper.h"

unsigned int bytesToUInt(unsigned char *firstByte) { // Little-Endian to Big-Endian conversion
    return (firstByte[3] << 24) + (firstByte[2] << 16) + (firstByte[1] << 8) + firstByte[0];
}

void uIntToBytes(unsigned int uInt, unsigned char *destination) { // Big-Endian to Little-Endian conversion
    destination[0] = (unsigned char) uInt & 0x000000FF;
    destination[1] = ((unsigned char) uInt & 0x0000FF00) >> 8;
    destination[2] = ((unsigned char) uInt & 0x00FF0000) >> 16;
    destination[3] = ((unsigned char) uInt & 0xFF000000) >> 24;
}
