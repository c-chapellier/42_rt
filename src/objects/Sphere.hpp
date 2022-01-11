#pragma once

#include "../header.hpp"

class Sphere : public Object
{
private:

public:
    Sphere(Transform transform, Material *material) : Object(transform, material) {}

    bool intersect(const Ray &ray, double min, hit_t &hit) const
    {
        Ray t_ray = this->transform.apply_backward(ray);

        Vec3 oc = t_ray.origin();

        double a = t_ray.direction().squared_length();
        double b = dot(oc, t_ray.direction());
        double c = oc.squared_length() - 1;
        double discriminant = b*b - a*c;

        if (discriminant < 0.) return false;

        double sqrt_d = sqrt(discriminant);
        double ts[2] = { (-b - sqrt_d) / a,  (-b + sqrt_d) / a };

        Vec3 inter;
        double t = this->get_min_t(ray, t_ray, 2, ts, inter);

        if (t < min || t > hit.t) return false;

        hit.t = t; 
        hit.intersection = inter;
        hit.normal = (hit.intersection - this->transform.apply_forward(Vec3(0, 0, 0))).unit_vector();
        hit.is_front_face = dot(ray.direction(), hit.normal) < 0;
        hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

        return true;
    }
};
