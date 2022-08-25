
#include "Plane.hpp"

Plane::Plane(Transform transform, double refractiveIndex, Material *material, Texture *texture)
    : Object(transform, refractiveIndex, material, texture)
{}

bool Plane::intersect(const Ray &ray, double min, hit_t &hit) const
{
    Ray t_ray = this->transform.apply_backward(ray);

    Vec3 normal = Vec3(1, 0, 0);

    Vec3 a = t_ray.origin();
    Vec3 k = t_ray.direction();

    double ts[] = {  a[0] / -k[0] };

    int n = this->filter_ts(1, ts);

    if (n == 0) return false;

    Vec3 global_inter, local_inter;
    double t = this->get_min_t(ray, t_ray, n, ts, global_inter, local_inter);

    if (t < min || t > hit.t) return false;

    hit.t = t;
    hit.local_inter = local_inter;
    hit.global_inter = global_inter;
    hit.normal = normal;
    hit.is_front_face = ray.direction().dot(hit.normal) < 0;
    hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

    hit.u = -(local_inter[2] <= 0 ?
                (local_inter[2] - (int)local_inter[2]) * 2 + 1 :
                (local_inter[2] - (int)local_inter[2]) * 2 - 1);
    hit.v = local_inter[1] < 0 ?
                (local_inter[1] - (int)local_inter[1]) * 2 + 1 :
                (local_inter[1] - (int)local_inter[1]) * 2 - 1;

    return true;
}