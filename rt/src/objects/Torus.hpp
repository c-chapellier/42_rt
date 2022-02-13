#pragma once

#include "../global.hpp"

#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"
#include "../objects/Object.hpp"

class Torus : public Object
{
private:
    double R, R2, r2, r2R2;
    
public:
    Torus(Transform transform, Material *material, Texture *texture, double R, double r);
    bool intersect(const Ray &ray, double min, hit_t &hit) const;
};
