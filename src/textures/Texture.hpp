#pragma once

#include "../global.hpp"

class Texture
{
public:
    virtual ~Texture() {};
    virtual Vec3 get_color(const Vec3 &p) const = 0;
};
