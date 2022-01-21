
#include "Uniform.hpp"

Uniform::Uniform(const Vec3 &color)
    : color(color)
{

}

Vec3 Uniform::get_color(const Vec3 &p) const
{
    (void)p;
    return this->color;
}