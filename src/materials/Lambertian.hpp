#pragma once

#include "../header.hpp"

class Lambertian : public Material
{
public:
    Vec3 albedo;

    Lambertian(const Vec3 &a) : albedo(a) {}

    bool scatter(const Ray &ray, const hit_t &hit, Vec3 &attenuation, Ray &scattered) const
    {
        Vec3 scatter_direction = hit.normal + this->random_in_unit_sphere().unit_vector();

        if (scatter_direction.near_zero())
                scatter_direction = hit.normal;

        scattered = Ray(hit.intersection, scatter_direction);
        attenuation = albedo;
        return true;
    }
};