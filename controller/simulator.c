#include <malloc.h>
#include <stdio.h>
#include "simulator.h"

void initialize(Simulator *simulator, int memorySize) {
    simulator->memory = malloc(sizeof(Memory));
    simulator->memory->startAddress = malloc(sizeof(unsigned int) * memorySize);
    simulator->memory->size = memorySize;
    simulator->processor = malloc(sizeof(Processor));
    initializeProcessor(simulator->processor);
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
    simulator->memory->startAddress = malloc(sizeof(unsigned int) * simulator->memory->size);

    for (int i = 0; i < 32; ++i) {
        (simulator->processor->registers + i)->data = 0; // Set registers to 0;
    }
}

void loadProgram(Simulator *simulator, char *path) {
    unsigned char tempArray[4];
    FILE *fp;
    fp = fopen(path, "r");
    int i = 0;
    if (fp == NULL) { exit(2); } // TODO: Make a useful debug statement including file path
    while (!feof(fp)) {
        fread(tempArray, sizeof(tempArray), 1, fp);
        *(simulator->memory->startAddress + i) = 0;
        for (int j = 0; j < 4; ++j) {
            unsigned int byte = (unsigned int) tempArray[j] << ((3 - j) * 8);
            *(simulator->memory->startAddress + i) = *(simulator->memory->startAddress + i) | byte;
        }
        ++i;
    }
    *(simulator->memory->startAddress + i - 1) = 0; // Off by one fix
    fclose(fp);
}

void run(Simulator *simulator) {
    // TODO: Make this.
}
