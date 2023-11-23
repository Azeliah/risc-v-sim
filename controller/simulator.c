#include "simulator.h"

void initialize(Simulator *simulator, int memorySize) {
    simulator->memory = malloc(sizeof(Memory));
    simulator->memory->startAddress = malloc(memorySize);
    for (int i = 0; i < memorySize; ++i) {
        simulator->memory->startAddress[i] = 0;
    }
    simulator->processor = malloc(sizeof(Processor));
    simulator->memoryMux = malloc(sizeof(Multiplexer));
    simulator->jalrMux = malloc(sizeof(Multiplexer));
    simulator->pcMux = malloc(sizeof(Multiplexer));
    simulator->pcAdd4 = malloc(sizeof(Adder));
    simulator->pcAddImm = malloc(sizeof(Adder));

    initializeProcessor(simulator->processor);

    simulator->memory->size = memorySize;
    simulator->programCounter = 0;
    simulator->pcIncrement = 4;
    simulator->postInstruction = 1;
    simulator->simulatorStatus = running;

    // Linking components
    simulator->processor->decoder->instructionInput = &simulator->instruction;

    simulator->ecallSignal = &simulator->processor->control->ecall;
    simulator->ecallType = &simulator->processor->registerModule->registers[17].data;

    simulator->pcMux->signal = &simulator->processor->alu->branchSignal;
    simulator->pcMux->input1 = &simulator->pcAdd4->output;
    simulator->pcMux->input2 = &simulator->pcAddImm->output;

    simulator->jalrMux->input1 = &simulator->pcMux->output;
    simulator->jalrMux->input2 = &simulator->processor->alu->output;
    simulator->jalrMux->signal = &simulator->processor->control->jalr;

    simulator->memoryMux->input1 = &simulator->processor->alu->output;
    simulator->memoryMux->input2 = &simulator->memory->memOutRegister.data;
    simulator->memoryMux->signal = &simulator->processor->control->memToReg;

    simulator->pcAddImm->input1 = &simulator->programCounter;
    simulator->pcAddImm->input2 = &simulator->processor->immediateModule->output;

    simulator->pcAdd4->input1 = &simulator->programCounter;
    simulator->pcAdd4->input2 = &simulator->pcIncrement;

    simulator->processor->registerModule->writeValue = &simulator->memoryMux->output;

    simulator->memory->writeData = &simulator->processor->registerModule->output2;
    simulator->memory->writeSignal = &simulator->processor->control->memWrite;
    simulator->memory->dataType = &simulator->processor->decoder->func3;
}

void tearDown(Simulator *simulator) {
    free(simulator->memory->startAddress);
    free(simulator->memory);
    free(simulator->memoryMux);
    free(simulator->jalrMux);
    free(simulator->pcMux);
    free(simulator->pcAdd4);
    free(simulator->pcAddImm);
    tearDownProcessor(simulator->processor);
    free(simulator->processor);
}

void reset(Simulator *simulator) {
    // Reset memory
    for (int i = 0; i < simulator->memory->size; ++i) {
        simulator->memory->startAddress[i] = 0;
    }

    // Reset registers
    for (int i = 0; i < 32; ++i) {
        simulator->processor->registerModule->registers[i].data = 0; // Set registers to 0;
    }

    simulator->programCounter = 0;
    simulator->simulatorStatus = running;
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
    while (simulator->simulatorStatus == running) {
        runCycle(simulator);
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
void runCycle(Simulator *simulator) {
    // Fetch instruction
    simulator->instruction = fetchInstruction(simulator->memory, simulator->programCounter);

    if (simulator->postInstruction) {
        printf("Line 0x%x: ", simulator->programCounter);
        postInstruction(simulator->instruction);
    }
    if (simulator->instruction == 0) {
        simulator->simulatorStatus = zeroInstruction;
    }
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
        loadData(simulator->memory, simulator->processor->alu->output);
    }
    if (simulator->processor->control->memWrite) {
        saveData(simulator->memory, simulator->processor->alu->output);
    }

    // Write to registers
    selectOutput(simulator->memoryMux);
    writeToRegister(simulator->processor->registerModule);

    // Update program counter
    executeAdder(simulator->pcAdd4);
    executeAdder(simulator->pcAddImm);
    selectOutput(simulator->pcMux);
    selectOutput(simulator->jalrMux);
    simulator->programCounter = simulator->jalrMux->output;
    if (*simulator->ecallSignal) simulator->simulatorStatus = ecallExit;
}
