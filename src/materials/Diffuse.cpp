
#include "Diffuse.hpp"

Diffuse::Diffuse() {}

bool Diffuse::reflect(const Ray &ray, const hit_t &hit, Vec3 &color, Ray &reflected) const
{
    (void)reflected;
    
    double theta = fabs(acos(ray.direction().unit_vector().dot(hit.normal.unit_vector())));

    if (theta > M_PI_2) theta = M_PI - theta;

    color = color * (1 - (2 * theta) / M_PI);

    return false;
}