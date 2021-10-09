#include "PngChunk.hpp"

PngChunk::PngChunk(){}

PngChunk::~PngChunk(){}

// polynome = x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
void PngChunk::computeCRC()
{
    uint32_t shift_register = 0xFFFFFFFF;
    uint32_t polynome = 79764919;

    for (unsigned int i = 0; i < 4; ++i) {
        char c = this->type[i];
        for (int j = 0; j < 8; ++j) {
            if((c << j && 128) ^ (shift_register << 31) == 1) {
                shift_register = (shift_register << 1) ^ polynome;
            } else {
                shift_register = (shift_register << 1);
            }
        }
    }

    for (unsigned int i = 0; i < this->length; ++i) {
        char c = this->data[i];
        for (int j = 0; j < 8; ++j) {
            if((c << j && 128) ^ (shift_register << 31) == 1) {
                shift_register = (shift_register << 1) ^ polynome;
            } else {
                shift_register = (shift_register << 1);
            }
        }
    }
}