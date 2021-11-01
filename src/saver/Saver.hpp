#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ios>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <filesystem>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

#include "./../headers/define.hpp"
#include "./../pixel/Pixel.hpp"

class Saver
{
    private:
        Saver();
        ~Saver();
    public:
        static void saveToBMP(int height, int width, std::vector<std::vector<Pixel>>);
};