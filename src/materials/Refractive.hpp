#pragma once

#include "../global.hpp"

#include "../components/Vec3.hpp"
#include "../components/Ray.hpp"
#include "../objects/Object.hpp"
#include "Material.hpp"

class Refractive : public Material
{
public:
    Refractive();
    int reflect(const Ray &ray, const hit_t &hit, double &refractiveIndex, Vec3 &color, Ray &reflected) const;
};
