#pragma once

#include "../global.hpp"

#include "../components/Vec3.hpp"

class BMP
{
public:
    static void write(const std::vector< std::vector<Vec3> > &pixels, const std::string &saveFile);
};