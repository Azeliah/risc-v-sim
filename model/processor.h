#ifndef RISC_V_SIM_PROCESSOR_H
#define RISC_V_SIM_PROCESSOR_H
#include "components/alu.h"
#include "components/aluControl.h"
#include "components/register.h"
#include "components/control.h"
#include "components/decoder.h"
#include "components/registerModule.h"
#include "components/multiplexer.h"
#include "components/immediateModule.h"

typedef struct Processor{
    RegisterModule *registerModule;
    Control *control;
    AluControl *aluControl;
    Alu *alu;
    Multiplexer *aluMux;
    ImmediateModule *immediateModule;
    Decoder *decoder;
} Processor;

void initializeProcessor(Processor *processor);

void tearDownProcessor(Processor *processor);
#endif //RISC_V_SIM_PROCESSOR_H
