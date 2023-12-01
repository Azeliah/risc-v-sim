#include "multiplexer.h"

void selectOutput(Multiplexer *multiplexer) { // If signal is non-zero, output input2 value.
    if (*multiplexer->signal) multiplexer->output = *multiplexer->input2;
    else multiplexer->output = *multiplexer->input1;
}
