#include <malloc.h>
#include <stdio.h>
#include "simulator.h"

void initialize(Simulator *simulator, int memorySize) {
    simulator->memory = malloc(sizeof(Memory));
    simulator->memory->startAddress = malloc(memorySize);
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
    simulator->memory->startAddress = malloc(simulator->memory->size);

    for (int i = 0; i < 32; ++i) {
        (simulator->processor->registers + i)->data = 0; // Set registers to 0;
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
        if (c < 0) *(simulator->memory->startAddress + i) = (unsigned char) 256 + c;
        else *(simulator->memory->startAddress + i) = (unsigned char) c;
    }
    fclose(fp);
}

void run(Simulator *simulator) {
    // TODO: Make this.
}
