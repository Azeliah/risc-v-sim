#ifndef RISC_V_SIM_BYTEHELPER_H
#define RISC_V_SIM_BYTEHELPER_H

unsigned int bytesToUInt(unsigned char *firstByte);

void uIntToBytes(unsigned int uInt, unsigned char *destination);

#endif //RISC_V_SIM_BYTEHELPER_H
