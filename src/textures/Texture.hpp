#pragma once

#include "../global.hpp"

class Texture
{
public:
    virtual ~Texture() {};
    virtual Vec3 get_color(const hit_t &hit) const = 0;
};
