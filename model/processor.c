#include <malloc.h>
#include "processor.h"

void initializeProcessor(Processor *processor) {
    // Reserve memory for components
    processor->registerModule = malloc(sizeof(RegisterModule));
    for (int i = 0; i < 32; ++i) {
        processor->registerModule->registers[i].data = 0; // Set registers to 0;
    }
    processor->control = malloc(sizeof(Control));
    processor->aluControl = malloc(sizeof(AluControl));
    processor->aluControl->opType = &processor->control->aluOp;
    processor->alu = malloc(sizeof(Alu));
    processor->aluMux = malloc(sizeof(Multiplexer));
    processor->decoder = malloc(sizeof(Decoder));
    processor->immediateModule = malloc(sizeof(ImmediateModule));

    // Linking components
    // RegisterModule
    processor->registerModule->register1 = &processor->decoder->r1Address;
    processor->registerModule->register2 = &processor->decoder->r2Address;
    processor->registerModule->writeSignal = &processor->control->registerWrite;
    processor->registerModule->writeRegister = &processor->decoder->rwAddress;

    // Control
    processor->control->input = &processor->decoder->opCode;

    // AluControl
    processor->aluControl->opType = &processor->control->aluOp;
    processor->aluControl->funct3 = &processor->decoder->funct3;
    processor->aluControl->bit30 = &processor->decoder->bit30;

    // Alu
    processor->alu->input1 = &processor->registerModule->output1;
    processor->alu->input2 = &processor->aluMux->output;
    processor->alu->op = &processor->aluControl->output;
    processor->alu->branchControl = &processor->control->branch;

    // AluMux
    processor->aluMux->input1 = &processor->registerModule->output2;
    processor->aluMux->input2 = &processor->immediateModule->output;
    processor->aluMux->signal = &processor->control->aluSource;

    // ImmediateModule
    processor->immediateModule->input = &processor->decoder->immediateBits;

}

void tearDownProcessor(Processor *processor) {
    free(processor->registerModule);
    free(processor->control);
    free(processor->aluControl);
    free(processor->alu);
    free(processor->aluMux);
    free(processor->decoder);
    free(processor->immediateModule);
}
