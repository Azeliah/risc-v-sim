#include "simulator.h"

void initialize(Simulator *simulator, int memorySize) {
    simulator->memory = malloc(sizeof(Memory));
    simulator->memory->startAddress = malloc(memorySize);
    simulator->processor = malloc(sizeof(Processor));
    simulator->memoryMux = malloc(sizeof(Multiplexer));
    simulator->pcMux = malloc(sizeof(Multiplexer));
    simulator->pcAdd4 = malloc(sizeof(Adder));
    simulator->pcAddImm = malloc(sizeof(Adder));

    initializeProcessor(simulator->processor);

    simulator->memory->size = memorySize;
    simulator->programCounter = 0;
    simulator->pcIncrement = 4;

    // Linking components
    simulator->processor->decoder->instructionInput = &simulator->instruction;

    simulator->pcMux->signal = &simulator->processor->alu->branchSignal;
    simulator->pcMux->input1 = &simulator->pcAdd4->output;
    simulator->pcMux->input2 = &simulator->pcAddImm->output;

    simulator->memoryMux->input1 = &simulator->processor->alu->output;
    simulator->memoryMux->input2 = &simulator->memory->memOutRegister.data;
    simulator->memoryMux->signal = &simulator->processor->control->memToReg;

    simulator->pcAddImm->input1 = &simulator->programCounter;
    simulator->pcAddImm->input2 = &simulator->processor->immediateModule->output;

    simulator->pcAdd4->input1 = &simulator->programCounter;
    simulator->pcAdd4->input2 = &simulator->pcIncrement;

    simulator->processor->registerModule->writeValue = &simulator->memoryMux->output;
}

void tearDown(Simulator *simulator) {
    free(simulator->memory->startAddress);
    free(simulator->memory);
    free(simulator->memoryMux);
    free(simulator->pcMux);
    free(simulator->pcAdd4);
    free(simulator->pcAddImm);
    tearDownProcessor(simulator->processor);
    free(simulator->processor);
}

void reset(Simulator *simulator) {
    // Re-allocate memory
    free(simulator->memory->startAddress);
    simulator->memory->startAddress = malloc(simulator->memory->size);

    for (int i = 0; i < 32; ++i) {
        simulator->processor->registerModule->registers[i].data = 0; // Set registers to 0;
    }
}

void loadProgram(Simulator *simulator, char *path) {
    char c;
    FILE *fp;
    fp = fopen(path, "r");
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    rewind(fp);
    if (fp == NULL) { exit(2); } // TODO: Make a useful debug statement including file path
    for (int i = 0; i < size; ++i) {
        c = (char) fgetc(fp);
        if (c < 0) simulator->memory->startAddress[i] = (unsigned char) 256 + c;
        else simulator->memory->startAddress[i] = (unsigned char) c;
    }
    fclose(fp);
}

/*
 * The run command simply continues execution until runCycle() returns a 0 value.
 */
void run(Simulator *simulator) {
    while (runCycle(simulator)) {

    }
}

/*
 * The runCycle simulates a single cycle in the processor and updates the values in the structures.
 * It operates with the phases of the single-cycle RISC-V implementation, that is:
 * * Fetch instruction from memory (incl. converting from Little-Endian to Big-Endian).
 * * Decode instruction and generate the immediate value.
 * * Execute the instruction in the ALU, using the control signals.
 * * Do necessary memory access - read or write.
 * * Write back from memory to the destination register (x0, if not otherwise specified).
 */
unsigned int runCycle(Simulator *simulator) {
    // Fetch instruction - conversion to Big-Endian happens in bytesToUInt()
    simulator->instruction = bytesToUInt(&simulator->memory->startAddress[simulator->programCounter]);

    // Decode instruction
    decodeInstruction(simulator->processor->decoder);
    generateImmediate(simulator->processor->immediateModule);

    // Set control signals and set registers
    updateControlSignals(simulator->processor->control);
    updateAluControlSignal(simulator->processor->aluControl);
    selectRegisters(simulator->processor->registerModule);

    // Select second input value for ALU and complete computation
    selectOutput(simulator->processor->aluMux);
    doOperation(simulator->processor->alu);

    // Access memory to read or write
    if (simulator->processor->control->memRead) {
        simulator->memory->memOutRegister.data = bytesToUInt(
                &simulator->memory->startAddress[simulator->processor->alu->output]);
    }
    if (simulator->processor->control->memWrite) {
        uIntToBytes(simulator->processor->registerModule->output2,
                    &simulator->memory->startAddress[simulator->processor->alu->output]);
    }

    // Write to registers
    selectOutput(simulator->memoryMux);
    writeToRegister(simulator->processor->registerModule);

    // Update program counter
    executeAdder(simulator->pcAdd4);
    executeAdder(simulator->pcAddImm);
    selectOutput(simulator->pcMux);
    simulator->programCounter = simulator->pcMux->output;

    return simulator->instruction;
}
