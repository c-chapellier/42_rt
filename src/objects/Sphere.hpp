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

        double coefs[3], ts[2];

        coefs[2] = t_ray.direction().squared_length();
        coefs[1] = t_ray.origin().dot(t_ray.direction());
        coefs[0] = t_ray.origin().squared_length() - 1;
        
        int n = EquationSolver::QuadraticSphere(coefs, ts);

        if (n == 0) return false;

        Vec3 inter;
        double t = this->get_min_t(ray, t_ray, n, ts, inter);

        if (t < min || t > hit.t) return false;

        hit.t = t;
        hit.intersection = inter;
        hit.normal = (hit.intersection - this->transform.apply_forward(Vec3(0, 0, 0))).unit_vector();
        hit.is_front_face = ray.direction().dot(hit.normal) < 0;
        hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

        return true;
    }
};
