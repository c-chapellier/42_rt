#pragma once

#include "../components/Vec3.hpp"
#include "../components/Ray.hpp"

class Material
{
public:
    virtual ~Material() {};
    virtual bool reflect(const Ray &ray, const hit_t &hit, Vec3 &color, Ray &reflected) const = 0;
};
