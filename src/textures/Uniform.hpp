#pragma once

#include "../global.hpp"

#include "Texture.hpp"

class Uniform : public Texture
{
private:
    Vec3 color;

public:
    Uniform(const Vec3 &color);
    Vec3 get_color(const hit_t &hit) const;
};
