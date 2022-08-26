#pragma once

#include "../global.hpp"

#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"

class Object
{
private:
    t_t get_min_t(const Ray &ray, const Ray &t_ray, int n, t_t *ts, Vec3 &global_inter, Vec3 &local_inter) const;

    virtual int filter_ts(int n, t_t *ts, const Ray &t_ray) const;

    virtual int get_ts(const Ray &t_ray, double *ts) const = 0;
    virtual Vec3 get_normal(const hit_t &hit) const = 0;
    virtual double get_u(const hit_t &hit, const Ray &t_ray) const = 0;
    virtual double get_v(const hit_t &hit, const Ray &t_ray) const = 0;
    
public:
    Transform transform;
    Material *material;
    Texture *texture;

    Object(Transform transform, Material *material, Texture *texture);
    virtual ~Object();
    bool intersect(const Ray &ray, double min, hit_t &hit) const;
};
