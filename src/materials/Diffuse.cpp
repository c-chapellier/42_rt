
#include "Diffuse.hpp"

Diffuse::Diffuse() {}

int Diffuse::reflect(const Ray &ray, const hit_t &hit, double &n, Vec3 &color, Ray &reflected) const
{
    (void)reflected, (void)n;
    
    double theta = fabs(acos(ray.direction().unit_vector().dot(hit.normal.unit_vector())));

    if (theta > M_PI_2) theta = M_PI - theta;

    color *= 1 - (M_2_PI * theta);

    return Material::REFLECTION_NONE;
}