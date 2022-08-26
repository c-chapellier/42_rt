
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
    (void)t_ray;

    // return a[2] + k[2] * hit.t;
    return -(hit.local_inter[2] <= 0 ?
                (hit.local_inter[2] - (int)hit.local_inter[2]) * 2 + 1 :
                (hit.local_inter[2] - (int)hit.local_inter[2]) * 2 - 1);
}

double Plane::get_v(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray;
    
    return hit.local_inter[1] < 0 ?
                (hit.local_inter[1] - (int)hit.local_inter[1]) * 2 + 1 :
                (hit.local_inter[1] - (int)hit.local_inter[1]) * 2 - 1;
}
