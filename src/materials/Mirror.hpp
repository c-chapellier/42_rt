#pragma once

#include "../global.hpp"

#include "../components/Vec3.hpp"
#include "../components/Ray.hpp"
#include "Material.hpp"

class Mirror : public Material
{
public:
    Mirror();
    bool reflect(const Ray &ray, const hit_t &hit, Vec3 &color, Ray &reflected) const;
};
