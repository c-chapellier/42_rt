
#include "Refractive.hpp"

Refractive::Refractive() {}

int Refractive::reflect(const Ray &ray, const hit_t &hit, double &refractiveIndex, Vec3 &color, Ray &reflected) const
{
    (void)color;

    double r = refractiveIndex / hit.object->refractiveIndex, c = abs(ray.direction().unit_vector().dot(hit.normal.unit_vector()));

    // refracted
    reflected = Ray(
        hit.global_inter,
        hit.global_inter + ray.direction().unit_vector() * r + (r*c - sqrt(1 - r*r*(1-c*c))) * hit.normal.unit_vector()
    );

    refractiveIndex = hit.object->refractiveIndex == refractiveIndex ? 1 : hit.object->refractiveIndex;

    return Material::REFLECTION_TOTAL;
}