#include <malloc.h>
#include "controller/simulator.h"
#include "test/test.h"

int main(int argc, char **argv) {
    Simulator *simulator = malloc(sizeof(Simulator));
    initialize(simulator, 0x800000);

    int test = 0;
    if (argc == 2) if (argv[1][0] == 't') test = 1;

    if (test) {
        // Run test environment
        int *resultArray = runTestSuite(simulator);
        if (resultArray) {
            printf("%d out of %d tests succeeded.", resultArray[0], resultArray[1]);
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
        else fp = "../test/task4/t14.bin";

        loadProgram(simulator, fp);
        run(simulator);
        printRegisters(simulator->processor->registerModule->registers);
    }

    tearDown(simulator);
    free(simulator);
    return 0;
}
