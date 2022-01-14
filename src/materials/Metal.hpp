#pragma once

#include "../header.hpp"

class Metal : public Material
{
public:
    Vec3 albedo;

    Metal(const Vec3 &a) : albedo(a) {}

    bool reflect(const Ray &ray, const hit_t &hit, Vec3 &attenuation, Ray &reflected) const
    {
        // reflected = Ray(hit.intersection, hit.intersection + ray.direction().unit_vector().reflect_on(hit.normal));
        // attenuation = albedo;
        // return (reflected.direction().dot(hit.normal) > 0);

        double theta = fabs(acos(ray.direction().unit_vector().dot(hit.normal.unit_vector())));

        if (theta > M_PI_2) theta = M_PI - theta;

        reflected = Ray(hit.intersection, ray.direction().unit_vector().reflect_on(hit.normal.unit_vector()));
        attenuation = this->albedo * (1 - (2 * theta) / M_PI);

        return true;

        reflected = Ray(hit.intersection, ray.direction().reflect_on(hit.normal));

        return false;
    }
};