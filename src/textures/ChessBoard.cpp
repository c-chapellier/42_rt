
#include "ChessBoard.hpp"

ChessBoard::ChessBoard(const Vec3 &color, const Vec3 &color2)
    : color(color), color2(color2)
{

}

Vec3 ChessBoard::get_color(const hit_t &hit) const
{
    int n = 10;
    int um = hit.u < 0 ? (int)(hit.u * n - 1) : (int)(hit.u * n);
    int vm = hit.v < 0 ? (int)(hit.v * n - 1) : (int)(hit.v * n);
 
    return ((um + vm) % 2) ? this->color : this->color2;
}
