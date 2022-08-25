#pragma once

#include "../components/Vec3.hpp"
#include "../components/Ray.hpp"

class Material
{
public:
    virtual ~Material() {};
    virtual int reflect(const Ray &ray, const hit_t &hit, double &n, Vec3 &color, Ray &reflected) const = 0;

    static const int REFLECTION_NONE = 0;
    static const int REFLECTION_PARTIAL = 1;
    static const int REFLECTION_TOTAL = 2;
};
