#ifndef RISC_V_SIM_CONVERSIONHELPER_H
#define RISC_V_SIM_CONVERSIONHELPER_H

unsigned int toLittleEndian(unsigned int num);

unsigned int signExtend(unsigned int num, int mostSignificant);

unsigned int getImmediateI(unsigned int instruction);

unsigned int getImmediateIShift(unsigned int instruction);

unsigned int getImmediateU(unsigned int instruction);

unsigned int getImmediateS(unsigned int instruction);

unsigned int getImmediateSB(unsigned int instruction);

unsigned int getImmediateUJ(unsigned int instruction);

#endif //RISC_V_SIM_CONVERSIONHELPER_H
