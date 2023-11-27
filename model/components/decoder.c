#include "decoder.h"

void decodeInstruction(Decoder *decoder) {
    unsigned int instruction = *decoder->instructionInput;
    decoder->opcode = instruction & 0x7F;
    decoder->r1Address = (instruction >> 15) & 0x1F;
    decoder->r2Address = (instruction >> 20) & 0x1F;
    decoder->rwAddress = (instruction >> 7) & 0x1F;
    decoder->immediateBits = instruction;
    decoder->func3 = (instruction >> 12) & 0x7;
    decoder->bit30 = (instruction >> 30) & 0x1;
}
