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
    public:
        Saver();
        ~Saver();

        void saveToPng(int width, int height);
};