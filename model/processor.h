#ifndef RISC_V_SIM_PROCESSOR_H
#define RISC_V_SIM_PROCESSOR_H
#include "components/alu.h"
#include "components/aluControl.h"
#include "components/register.h"
#include "components/control.h"
#include "components/decoder.h"

typedef struct Processor{
    Register *registers;
    Control *control;
    AluControl *aluControl;
    Alu *alu;
    Decoder *decoder;
} Processor;

void initializeProcessor(Processor *processor);

void tearDownProcessor(Processor *processor);
#endif //RISC_V_SIM_PROCESSOR_H
