#pragma once

#include "../header.hpp"
#include <complex>

#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))
#define QUARTIC(x) ((x) * (x) * (x) * (x))

class Torus : public Object
{
private:
    double R, R2, r2, r2R2;
    
public:
    Torus(Transform transform, Material *material, double R, double r)
    : Object(transform, material), R(R), R2(R * R), r2(r * r), r2R2(r2 + R2)
    {
    }

    bool intersect(const Ray &ray, double min, hit_t &hit) const
    {
        Ray t_ray = this->transform.apply_backward(ray).unit_ray();

        double x0 = t_ray.origin()[0];
        double y00 = t_ray.origin()[1];
        double z0 = t_ray.origin()[2];

        double a = t_ray.direction()[0];
        double b = t_ray.direction()[1];
        double c = t_ray.direction()[2];

        double x0a = t_ray.origin()[0] * a;
        double y0b = t_ray.origin()[1] * b;
        double z0c = t_ray.origin()[2] * c;

        double a2 = a * a;
        double b2 = b * b;
        double c2 = c * c;

        double x02 = x0 * x0;
        double y02 = y00 * y00;
        double z02 = z0 * z0;

        double a2b2c2 = a2 + b2 + c2;
        double x0ay0bz0c = x0a + y0b + z0c;
        double x02y02z02 = x02 + y02 + z02;

        double coefs[5], ts[4];

        coefs[4] = SQUARE(a2b2c2);
        coefs[3] = 4 * a2b2c2 * x0ay0bz0c;
        coefs[2] = 2 * a2b2c2 * (x02y02z02 - r2R2) + 4*SQUARE(x0ay0bz0c) + 4*R2*b2;
        coefs[1] = 4 * (x02y02z02 - r2R2) * x0ay0bz0c + 8*R2*y0b;
        coefs[0] = SQUARE(x02y02z02 - r2R2) - 4*R2*(r2 - y02);

        coefs[4] = 1;
        coefs[3] = 1;
        coefs[2] = 1;
        coefs[1] = 1;
        coefs[0] = 1;
        
        int n = SolveQuartic(coefs, ts);

        PRINT("n = " << n);
        for (int i = 0; i < n; ++i)
            PRINT("ts = " << ts[i]);
        exit(1);

        if (n == 0) return false;

        Vec3 inter;
        double t = this->get_min_t(ray, t_ray, n, ts, inter);

        if (t < min || t > hit.t) return false;

        hit.t = t;
        hit.intersection = inter;

        Vec3 t_inter = this->transform.apply_backward(hit.intersection);
        Vec3 q = Vec3(t_inter[0], t_inter[1], 0).unit_vector() * this->R;

        hit.normal = (hit.intersection - this->transform.apply_forward(q)).unit_vector();
        hit.is_front_face = ray.direction().dot(hit.normal) < 0;
        hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

        return true;
    }
};
