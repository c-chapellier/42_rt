
#include "ChessBoard.hpp"

ChessBoard::ChessBoard(const Vec3 &color, const Vec3 &color2, int object_type)
    : color(color), color2(color2), object_type(object_type)
{

};

Vec3 ChessBoard::get_color(const Vec3 &p) const
{
    switch (this->object_type)
    {
    case SPHERE:
    {
        int y = (int)(p[1] / .3);
        y = p[1] < 0 ? y + 1 : y;
        // y = 0;

        double angle = atan(p[0] / p[2]);

        PRINT("p: " << p[0]);
        PRINT("angle: " << angle);

        int theta = (int)(angle / (M_PI / 12));
        theta = angle < 0 ? theta + 1 : theta;

        return ((y + theta) % 2) ? this->color : this->color2;
    }
    case TORUS:
    {
        int z = (int)(p[2] / .01);
        z = p[2] < 0 ? z + 1 : z;
        // z = 0;

        double angle = atan(p[1] / p[0]);

        PRINT("p: " << p[0]);
        PRINT("angle: " << angle);

        int theta = (int)(angle / (M_PI / 12));
        theta = angle < 0 ? theta + 1 : theta;

        return ((z + theta) % 2) ? this->color : this->color2;
    }
    case PLANE:
    {
        int y = (int)(p[1] / 2);
        y = p[1] < 0 ? y + 1 : y;

        int z = (int)(p[2] / 2);
        z = p[2] < 0 ? z + 1 : z;

        return ((y + z) % 2) ? this->color : this->color2;
    }
    default:
        return this->color;
    }
}