#pragma once

#include "../global.hpp"

#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"
#include "../objects/Object.hpp"

class MobiusTape : public Object
{
private:
    double r;
    
    int filter_ts(int n, double *ts, const Ray &t_ray) const;
    Vec3 normal(const Vec3 &p) const;

public:
    MobiusTape(Transform transform, Material *material, Texture *texture);
    bool intersect(const Ray &ray, double min, hit_t &hit) const;
};
