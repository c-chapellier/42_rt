#pragma once

#include "../header.hpp"

class Diffuse : public Material
{
public:
    Vec3 albedo;

    Diffuse(const Vec3 &a) : albedo(a) {}

    bool reflect(const Ray &ray, const hit_t &hit, Vec3 &attenuation, Ray &reflected) const
    {
        double theta = fabs(acos(ray.direction().unit_vector().dot(hit.normal.unit_vector())));

        if (theta > M_PI_2) theta = M_PI - theta;

        // reflected = Ray(hit.intersection, ray.direction().reflect_on(hit.normal));
        attenuation = this->albedo * (1 - (2 * theta) / M_PI);

        return false;
    }
};