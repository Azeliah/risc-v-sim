#include "test.h"

int *runTestSuite(Simulator *simulator) {
    int *resultArray = malloc(sizeof(int) * 2);

    int *numTestGroups = malloc(sizeof(int));
    char **testGroups = getTestDirectories(numTestGroups);

    for (int i = 0; i < *numTestGroups; ++i) {
        int *numTests = malloc(sizeof(int));
        char **testBasePaths = getTests(*(testGroups + i), numTests);

        for (int j = 0; j < *numTests; ++j) {
            resultArray[0] += runTest(simulator, testBasePaths[j]);
            resultArray[1]++;
        }

        free(numTests);
        free(testBasePaths);
    }
    free(numTestGroups);
    free(testGroups);
    return resultArray;
}

int runTest(Simulator *simulator, char *basePath) {
    // Create paths
    char *testProgramPath = strdup(basePath);
    strcat(testProgramPath, ".bin");
    char *expectedResultPath = strdup(basePath);
    strcat(expectedResultPath, ".res");

    // Load program into simulator and run it
    loadProgram(simulator, testProgramPath);
    run(simulator);

    // Get expected results from file
    unsigned int *expectedResult = getExpectedTestResult(expectedResultPath);

    int testResult = 1;
    for (int i = 0; i < 32; ++i) {
        if ((simulator->processor->registers + i)->data != *(expectedResult + i)) {
            testResult = 0;
            break; // If a result does not match, the test has already failed
            // TODO: Create meaningful error message.
        }
    }
    reset(simulator); // Test has concluded and the simulator is reset
    free(expectedResult);
    return testResult;
}

char **getTestDirectories(int *numTestGroups) {
    return (char **) 0;
}

char **getTests(char *directory, int *numTests) {
    return (char **) 0;
}

unsigned int *getExpectedTestResult(char *path) { // For comparing the 32 registers.
    unsigned int *nums = malloc(sizeof(int) * 32);
    unsigned char tempArray[4];
    FILE *fp;
    fp = fopen(path, "r");
    int i = 0;
    if (fp == NULL) { exit(2); } // TODO: Make a useful debug statement including file path
    while (!feof(fp)) {
        if (i == 32) break; // Off by one fix
        fread(tempArray, sizeof(tempArray), 1, fp);
        *(nums + i) = 0;
        for (int j = 0; j < 4; ++j) {
            unsigned int byte = (unsigned int) tempArray[j] << ((3 - j) * 8);
            *(nums + i) = *(nums + i) | byte;
        }
        ++i;
    }
    fclose(fp);
    return nums;
}
