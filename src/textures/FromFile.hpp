#pragma once

#include "../global.hpp"

#include "Texture.hpp"

class FromFile : public Texture
{
private:
    int width, height, bpp;
    uint8_t *texture;

    ~FromFile();

public:
    FromFile(const std::string &filename);
    Vec3 get_color(const hit_t &hit) const;
};
