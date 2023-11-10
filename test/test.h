#ifndef RISC_V_SIM_TEST_H
#define RISC_V_SIM_TEST_H

#include <dirent.h>
#include <string.h>

#include "../controller/simulator.h"

typedef struct List {
    char *string;
    struct List *next;
} List;

int *runTestSuite(Simulator *simulator);

int runTest(Simulator *simulator, List *basePath);

List *getTestDirectories();

List *getTests(List *directories);

unsigned int *getExpectedTestResult(char *path);

#endif //RISC_V_SIM_TEST_H
