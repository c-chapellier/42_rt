#pragma once

#include "../global.hpp"

#include "../components/Vec3.hpp"

class Saver
{
public:
    static void toBMP(const std::string &file, const std::vector< std::vector<Vec3> > &pixels);
};