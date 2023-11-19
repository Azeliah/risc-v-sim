#include "adder.h"

void execute(Adder *adder) {
    adder->output = *adder->input1 + *adder->input2;
}
