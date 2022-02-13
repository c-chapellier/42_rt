#pragma once

#include "../global.hpp"

#include "../components/Vec3.hpp"

class Saver
{
public:
    static void toBMP(const std::vector< std::vector<Vec3> > &pixels, const std::string &saveFile);
};