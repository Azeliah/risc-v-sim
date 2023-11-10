#include "test.h"

int *runTestSuite(Simulator *simulator) {
    int *resultArray = malloc(sizeof(int) * 2);
    *resultArray = 0;
    *(resultArray + 1) = 0;

    List *testGroups = getTestDirectories();
    if (!testGroups->string) return NULL;
    List *nodeI = testGroups;
    while (1) {
        List *testBasePaths = getTests(nodeI);
        if (!testBasePaths->string) return NULL;
        List *nodeJ = testBasePaths;
        while (1) {
            *resultArray += runTest(simulator, nodeJ);
            (*(resultArray + 1))++;
            List *tempJ = nodeJ;
            nodeJ = nodeJ->next;
            free(tempJ->string);
            free(tempJ);
            if (nodeJ->string == NULL) {
                free(nodeJ);
                break;
            }
        }
        List *tempI = nodeI;
        nodeI = nodeI->next;
        free(tempI->string);
        free(tempI);
        if (nodeI->string == NULL) {
            free(nodeI);
            break;
        }
    }
    return resultArray;
}

int runTest(Simulator *simulator, List *basePath) {
    // Create paths
    char *testProgramPath = strdup(basePath->string);
    strcat(testProgramPath, ".bin");
    char *expectedResultPath = strdup(basePath->string);
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

List *getTestDirectories() {
    // TODO: Make a solution that works for both Windows and Linux, if possible.
    char *testDirectory = "../test";
    DIR *dir = opendir(testDirectory);

    if (!dir) {
        printf("No directory stream found at path %s", testDirectory);
        return NULL;
    }

    List *testDirectories = malloc(sizeof(List));
    testDirectories->string = NULL;
    testDirectories->next = NULL;

    List *current = testDirectories;
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
            List *newNode = malloc(sizeof(List));
            newNode->string = NULL;
            current->string = newPath;
            current->next = newNode;
            current = newNode;
        } else break; // Directories are listed first in the stream.
    }
    closedir(dir);
    return testDirectories;
}

List *getTests(List *directory) {
    DIR *dir = opendir(directory->string);

    if (!dir) {
        printf("No directory stream found at path %s", directory->string);
        return NULL;
    }

    List *testCases = malloc(sizeof(List));
    testCases->string = NULL;
    testCases->next = NULL;
    List *current = testCases;
    List *previous = NULL;
    struct dirent *newFile;
    while ((newFile = readdir(dir))) {
        if (!strcmp(newFile->d_name, ".") || !strcmp(newFile->d_name, "..")) continue;
        char *newPath = malloc(strlen(directory->string) + strlen(newFile->d_name) + 2);
        sprintf(newPath, "%s/%s", directory->string, newFile->d_name);
        int isDirectory = 1;
        for (int i = (int) strlen(directory->string) + 1;
             *(newPath + i) != '\0'; ++i) { // Assuming no dots in directory names.
            if (*(newPath + i) == '.') { // Scrapping the file extension.
                *(newPath + i) = '\0';
                isDirectory = 0;
                break;
            }
        }
        if (!isDirectory) {
            if (previous != NULL) {
                if (strcmp(previous->string, newPath) == 0) {
                    free(newPath);
                    continue;
                }
            }
            List *newNode = malloc(sizeof(List));
            newNode->string = NULL;
            current->string = newPath;
            current->next = newNode;
            previous = current;
            current = newNode;
        } else {
            free(newPath);
        }
    }
    closedir(dir);
    return testCases;
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
