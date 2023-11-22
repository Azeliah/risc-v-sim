#ifndef RISC_V_SIM_CONVERSIONHELPER_H
#define RISC_V_SIM_CONVERSIONHELPER_H

unsigned int bytesToUInt(unsigned char *firstByte);

void uIntToBytes(unsigned int uInt, unsigned char *destination);

unsigned int signExtend(unsigned int num, int mostSignificant);

unsigned int getUImmediateI(unsigned int instruction);

int getImmediateI(unsigned int instruction);

int getImmediateU(unsigned int instruction);

int getImmediateS(unsigned int instruction);

int getImmediateSB(unsigned int instruction);

int getImmediateUJ(unsigned int instruction);

#endif //RISC_V_SIM_CONVERSIONHELPER_H
