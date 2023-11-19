#include "multiplexer.h"

void selectOutput(Multiplexer *multiplexer) {
    if (*multiplexer->signal) multiplexer->output = *multiplexer->input2;
    else multiplexer->output = *multiplexer->input1;
}
