#include <malloc.h>
#include "controller/simulator.h"
#include "test/test.h"

int main(int argc, char **argv) {
    Simulator *simulator = malloc(sizeof(Simulator));
    initialize(simulator, 0x10000);

    int test = 0;
    if (argc == 2) if (**(argv + 1) == 't') test = 1;

    if (test) {
        // Run test environment
        int *resultArray = runTestSuite(simulator);
        if (resultArray) {
            printf("%d out of %d tests succeeded.", *resultArray, *(resultArray + 1));
        }
        free(resultArray);
    } else {
        /*
         * Steps of execution:
         *
         * 1. Set up the simulator
         *
         * 2. Load the program to be executed into the memory
         *
         * 3. Execute program(s) and print register contents after program(s)
         *
         * 4. Tear down memory allocations
         */
        char *fp;
        if (argc > 2) fp = argv[1];
        else fp = "../test/task1/addlarge.bin";

        loadProgram(simulator, fp);
        printRegisters(simulator->processor->registers);
    }
    tearDown(simulator);
    free(simulator);
    return 0;
}
