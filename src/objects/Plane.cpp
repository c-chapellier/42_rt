
#include "Plane.hpp"

Plane::Plane(Transform transform, Material *material, Texture *texture)
    : Object(transform, material, texture)
{}

int Plane::get_ts(const Ray &t_ray, double *ts) const
{
    ts[0] = t_ray.origin()[0] / -t_ray.direction()[0];

    return 1;
}

Vec3 Plane::get_normal(const hit_t &hit) const
{
    (void)hit;
    return this->transform.apply_forward(Vec3(0, 0, 0)) - this->transform.apply_forward(Vec3(1, 0, 0));;
}

double Plane::get_u(const hit_t &hit, const Ray &t_ray) const
{
    return t_ray.origin()[2] + t_ray.direction()[2] * hit.t.local;
}

double Plane::get_v(const hit_t &hit, const Ray &t_ray) const
{
    return t_ray.origin()[1] + t_ray.direction()[1] * hit.t.local;
}
