#ifndef RISC_V_SIM_TEST_H
#define RISC_V_SIM_TEST_H

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "../controller/simulator.h"

int *runTestSuite(Simulator *simulator);

void runTestGroup(Simulator *simulator, int *resultArray, char *directory);

int runTest(Simulator *simulator, char *testPath);

unsigned int *getExpectedTestResult(char *path);

#endif //RISC_V_SIM_TEST_H
