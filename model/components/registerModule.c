#include "registerModule.h"

void selectRegisters(RegisterModule *registerModule) {
    registerModule->output1 = registerModule->registers[*registerModule->register1].data;
    registerModule->output2 = registerModule->registers[*registerModule->register2].data;
}

void writeToRegister(RegisterModule *registerModule) {
    if (*registerModule->writeSignal) {
        if (!*registerModule->writeRegister) { // If writeRegister is 0, no update is needed.
            registerModule->registers[*registerModule->writeRegister].data = *registerModule->writeValue;
        }
    }
}
