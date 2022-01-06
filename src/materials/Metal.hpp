#pragma once

#include "../header.hpp"

class Metal : public Material
{
public:
    Vec3 albedo;

    Metal(const Vec3 &a) : albedo(a) {}

    bool scatter(const Ray &ray, const hit_t &hit, Vec3 &attenuation, Ray &scattered) const
    {
        Vec3 reflected = unit_vector(ray.direction()).reflect_on(hit.normal);
        scattered = Ray(hit.intersection, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), hit.normal) > 0);
    }
};