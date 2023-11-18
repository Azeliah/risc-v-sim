#include <malloc.h>
#include "processor.h"

void initializeProcessor(Processor *processor) {
    processor->registers = malloc(sizeof(Register) * 32);
    for (int i = 0; i < 32; ++i) {
        processor->registers[i].data = 0; // Set registers to 0;
    }
    processor->control = malloc(sizeof(Control));
    processor->aluControl = malloc(sizeof(AluControl));
    processor->aluControl->opType = processor->control->aluOp;
    processor->alu = malloc(sizeof(Alu));
}

void tearDownProcessor(Processor *processor) {
    free(processor->registers);
    free(processor->control);
    free(processor->aluControl);
    free(processor->alu);
}
