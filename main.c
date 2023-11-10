#include <malloc.h>
#include "controller/simulator.h"

int main() {
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

    Simulator *simulator = malloc(sizeof(Simulator));
    initialize(simulator, 0x10000);
    printRegisters(simulator);
    tearDown(simulator);
    free(simulator);
    return 0;
}
