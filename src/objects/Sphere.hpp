#pragma once

#include "../global.hpp"

#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"
#include "../objects/Object.hpp"

class Sphere : public Object
{
public:
    Sphere(Transform transform, Material *material, Texture *texture);
    bool intersect(const Ray &ray, double min, hit_t &hit) const;
};
