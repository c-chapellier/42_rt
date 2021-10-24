#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ios>

#include "./../headers/define.hpp"

class Saver
{
    private:
        void writePngHeader(std::ofstream *outfile);
        void writePngChunkIHDR(std::ofstream *outfile, int width, int height);
        void writePngChunkPLTE(std::ofstream *outfile);
        void writePngChunkIDAT(std::ofstream *outfile);
        void writePngChunkIEND(std::ofstream *outfile);
    public:
        Saver();
        ~Saver();

        void saveToPng(int width, int height);
};