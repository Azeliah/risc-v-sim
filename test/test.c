#include "test.h"

int *runTestSuite(Simulator *simulator) {
    int *resultArray = malloc(sizeof(int) * 2);
    *resultArray = 0;
    *(resultArray + 1) = 0;

    char *testDirectory = "../test";
    DIR *dir = opendir(testDirectory);

    if (!dir) {
        printf("No directory stream found at path %s", testDirectory);
        return NULL;
    }

    struct dirent *newDirectory;

    while ((newDirectory = readdir(dir))) {
        if (!strcmp(newDirectory->d_name, ".") || !strcmp(newDirectory->d_name, "..")) continue;
        char *newPath = malloc(strlen(testDirectory) + strlen(newDirectory->d_name) + 2);
        sprintf(newPath, "%s/%s", testDirectory, newDirectory->d_name);
        int isDirectory = 1;
        for (int i = (int) strlen(testDirectory) + 1;
             *(newPath + i) != '\0'; ++i) { // Assuming no dots in directory names.
            if (*(newPath + i) == '.') {
                free(newPath);
                isDirectory = 0;
                break;
            }
        }
        if (isDirectory) {
            runTestGroup(simulator, resultArray, newPath);
            free(newPath);
        } else break; // Directories are listed first in the stream.
    }

    closedir(dir);

    return resultArray;
}

void runTestGroup(Simulator *simulator, int *resultArray, char *directory) {
    DIR *dir = opendir(directory);

    if (!dir) {
        printf("No directory stream found at path %s", directory);
        return;
    }

    struct dirent *newFile;
    while ((newFile = readdir(dir))) {
        if (!strcmp(newFile->d_name, ".") || !strcmp(newFile->d_name, "..")) continue;
        char *newPath = malloc(strlen(directory) + strlen(newFile->d_name) + 2);
        sprintf(newPath, "%s/%s", directory, newFile->d_name);
        int isTestFile = 0;
        for (int i = (int) strlen(directory) + 1;
             *(newPath + i) != '\0'; ++i) { // Assuming no dots in directory names.
            if (*(newPath + i) == '.') {
                if (*(newPath + i + 1) == 'b') {
                    isTestFile = 1;
                    break;
                }
            }
        }
        if (isTestFile) {
            *resultArray += runTest(simulator, newPath);
            (*(resultArray + 1))++;
        }
        free(newPath);
    }
    closedir(dir);
}

int runTest(Simulator *simulator, char *testPath) {
    // Load program into simulator and run it
    loadProgram(simulator, testPath);
    run(simulator);

    // Get expected results from file
    char *expectedResultPath = strdup(testPath);
    *(expectedResultPath + strlen(expectedResultPath) - 3) = 'r';
    *(expectedResultPath + strlen(expectedResultPath) - 2) = 'e';
    *(expectedResultPath + strlen(expectedResultPath) - 1) = 's';
    unsigned int *expectedResult = getExpectedTestResult(expectedResultPath);

    int testResult = 1;
    for (int i = 0; i < 32; ++i) {
        if ((simulator->processor->registers + i)->data != *(expectedResult + i)) {
            testResult = 0;
            break; // If a result does not match, the test has already failed
            // TODO: Create meaningful logging message.
        }
    }
    reset(simulator); // Test has concluded and the simulator is reset
    free(expectedResult);
    return testResult;
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
