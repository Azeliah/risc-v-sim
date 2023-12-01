#include "adder.h"

void executeAdder(Adder *adder) {
    adder->output = *adder->input1 + *adder->input2;
}
