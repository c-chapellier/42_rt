#pragma once

#include "../global.hpp"

#include "Texture.hpp"

class ChessBoard : public Texture
{
private:
    Vec3 color, color2;
    int object_type;

public:
    ChessBoard(const Vec3 &color, const Vec3 &color2, int object_type);
    Vec3 get_color(const Vec3 &p) const;
};
