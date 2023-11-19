#include "simulator.h"

void initialize(Simulator *simulator, int memorySize) {
    simulator->memory = malloc(sizeof(Memory));
    simulator->memory->startAddress = malloc(memorySize);
    simulator->memory->size = memorySize;
    simulator->processor = malloc(sizeof(Processor));
    simulator->programCounter = 0;
    initializeProcessor(simulator->processor);
    // Linking components
    simulator->processor->decoder->instructionInput = &simulator->instruction;
}

void tearDown(Simulator *simulator) {
    free(simulator->memory->startAddress);
    free(simulator->memory);
    tearDownProcessor(simulator->processor);
    free(simulator->processor);
}

void reset(Simulator *simulator) {
    // Re-allocate memory
    free(simulator->memory->startAddress);
    simulator->memory->startAddress = malloc(simulator->memory->size);

    for (int i = 0; i < 32; ++i) {
        simulator->processor->registers[i].data = 0; // Set registers to 0;
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
int runCycle(Simulator *simulator) {
    // Fetching instruction - conversion to Big-Endian happens in bytesToUInt()
    simulator->instruction = bytesToUInt(&simulator->memory->startAddress[simulator->programCounter]);
    // Decoding instruction
    return 0;
}
