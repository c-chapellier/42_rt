#pragma once

#include "../global.hpp"

#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"

class Object
{
protected:
    int filter_ts(int n, double *ts) const;
    double get_min_t(const Ray &ray, const Ray &t_ray, int n, double *ts, Vec3 &global_inter, Vec3 &local_inter) const;

public:
    Material *material;
    Transform transform;
    Texture *texture;

    Object(Transform transform, Material *material, Texture *texture);
    virtual ~Object() {};
    virtual bool intersect(const Ray &ray, double min, hit_t &hit) const = 0;
};
