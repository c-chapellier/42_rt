
#include "Mirror.hpp"

Mirror::Mirror() {}

int Mirror::reflect(const Ray &ray, const hit_t &hit, double &n, Vec3 &color, Ray &reflected) const
{
    (void)color, (void)n;

    // double theta = fabs(acos(ray.direction().unit_vector().dot(hit.normal.unit_vector())));

    // if (theta > M_PI_2) theta = M_PI - theta;

    reflected = Ray(hit.global_inter, hit.global_inter + ray.direction().unit_vector().reflect_on(hit.normal.unit_vector()));

    // return reflected.direction().dot(hit.normal) > 0;
    return Material::REFLECTION_TOTAL;
}