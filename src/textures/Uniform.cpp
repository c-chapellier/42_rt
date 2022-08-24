
#include "Uniform.hpp"

Uniform::Uniform(const Vec3 &color)
    : color(color)
{

}

Vec3 Uniform::get_color(const hit_t &hit) const
{
    (void)hit;
    return this->color;
}