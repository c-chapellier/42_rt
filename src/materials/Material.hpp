#pragma once

#include "../header.hpp"

class Material {
public:
    virtual bool reflect(const Ray &ray, const hit_t &hit, Vec3 &attenuation, Ray &reflected) const = 0;

    Vec3 random_in_unit_sphere() const
    {
        while (true) {
            Vec3 p = Vec3(RANDOM(-1, 1), RANDOM(-1, 1), RANDOM(-1, 1));
            if (p.squared_length() >= 1) continue;
            return p;
        }
    }
};
