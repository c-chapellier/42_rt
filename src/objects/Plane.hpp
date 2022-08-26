#pragma once

#include "../global.hpp"

#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"
#include "../objects/Object.hpp"

class Plane : public Object
{
private:
    int get_ts(const Ray &t_ray, double *ts) const;
    Vec3 get_normal(const hit_t &hit) const;
    double get_u(const hit_t &hit, const Ray &t_ray) const;
    double get_v(const hit_t &hit, const Ray &t_ray) const;
    
public:
    Plane(Transform transform, Material *material, Texture *texture);
};
