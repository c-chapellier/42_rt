#pragma once

#include "../global.hpp"

#include "../components/Vec3.hpp"
#include "../components/Ray.hpp"
#include "Material.hpp"

class Diffuse : public Material
{
public:
    Diffuse();
    int reflect(const Ray &ray, const hit_t &hit, double &n, Vec3 &color, Ray &reflected) const;
};