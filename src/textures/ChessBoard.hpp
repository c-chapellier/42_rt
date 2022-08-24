#pragma once

#include "../global.hpp"

#include "Texture.hpp"

class ChessBoard : public Texture
{
private:
    Vec3 color, color2;

public:
    ChessBoard(const Vec3 &color, const Vec3 &color2);
    Vec3 get_color(const hit_t &hit) const;
};
