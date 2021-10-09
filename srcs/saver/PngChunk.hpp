#pragma once

#include <string>

class PngChunk
{
    private:
        unsigned int length;
        std::string type; // 4 bytes
        std::string data; // length bytes
        unsigned int crc;
    public:
        PngChunk();
        ~PngChunk();

        void computeCRC();
};