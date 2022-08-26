#pragma once

#include "../global.hpp"

#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"
#include "../objects/Object.hpp"

class Torus : public Object
{
private:
    double R, r, R2, r2, r2R2;
    
    int get_ts(const Ray &t_ray, double *ts) const;
    Vec3 get_normal(const hit_t &hit) const;
    double get_u(const hit_t &hit) const;
    double get_v(const hit_t &hit) const;

public:
    Torus(Transform transform, Material *material, Texture *texture, double R, double r);
};
