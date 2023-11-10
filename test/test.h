#ifndef RISC_V_SIM_TEST_H
#define RISC_V_SIM_TEST_H

#include <string.h>

#include "../controller/simulator.h"

int *runTestSuite(Simulator *simulator);

int runTest(Simulator *simulator, char *basePath);

char **getTestDirectories(int *numTestGroups);

char **getTests(char *directory, int *numTests);

unsigned int *getExpectedTestResult(char *path);

#endif //RISC_V_SIM_TEST_H
