#pragma once

#include "../header.hpp"

class Sphere : public Object
{
private:
    Vec3 center;
    double radius;

public:
    Sphere(Vec3 center, double radius, Material *material) : Object(material)
    {
        this->center = center;
        this->radius = radius;
    }

    bool intersect(const Ray &ray, double min, hit_t &hit) const
    {
        Vec3 oc = ray.origin() - this->center;

        double a = ray.direction().squared_length();
        double b = dot(oc, ray.direction());
        double c = oc.squared_length() - radius * radius;
        double discriminant = b*b - a*c;

        if (discriminant < 0.) return false;

        double sqrt_d = sqrt(discriminant);
        double t = (-b - sqrt_d) / a;

        if (t < min || t > hit.t)
        {
            t = (-b + sqrt_d) / a;
            if (t < min || t > hit.t) return false;
        }

        hit.t = t;
        hit.intersection = ray.point_at_parameter(t);
        hit.normal = (hit.intersection - this->center) / this->radius;
        hit.is_front_face = dot(ray.direction(), hit.normal) < 0;
        hit.normal = hit.is_front_face ? hit.normal : -hit.normal;
        return true;
    }
};
