#pragma once

#include "../global.hpp"

class Uniform : public Texture
{
private:
    Vec3 color;

public:
    Uniform(const Vec3 &color) : color(color) {};

    Vec3 get_color(const Vec3 &p)
    {
        return this->color;
    }
};
