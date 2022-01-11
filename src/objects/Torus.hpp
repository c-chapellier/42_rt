#pragma once

#include "../header.hpp"
#include <complex>

#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))
#define QUARTIC(x) ((x) * (x) * (x) * (x))

class Torus : public Object
{
private:

public:
    Torus(Transform transform, Material *material) : Object(transform, material) {}

    bool intersect(const Ray &ray, double min, hit_t &hit) const
    {
        Ray t_ray = this->transform.apply_backward(ray).unit_ray();

        double R = 1;
        double r = .3;

        double x0 = t_ray.origin()[0];
        double y00 = t_ray.origin()[1];
        double z0 = t_ray.origin()[2];

        double a = t_ray.direction()[0];
        double b = t_ray.direction()[1];
        double c = t_ray.direction()[2];

        double a2 = a*a;
        double b2 = b*b;
        double c2 = c*c;

        double x02 = x0*x0;
        double y02 = y00*y00;
        double z02 = z0*z0;

        double R2 = R*R;
        double r2 = r*r;

        double coefs[5], ts[4];

        coefs[4] = SQUARE(a2 + b2 + c2);
        coefs[3] = 4 * (a2 + b2 + c2) * (x0*a + y00*b + z0*c);
        coefs[2] = 2 * (a2 + b2 + c2) * (x02 + y02 + z02 - (r2 + R2)) + 4*SQUARE(x0*a + y00*b + z0*c) + 4*R2*b2;
        coefs[1] = 4 * (x02 + y02 + z02 - (r2 + R2)) * (x0*a + y00*b + z0*c) + 8*R2*y00*b;
        coefs[0] = SQUARE(x02 + y02 + z02 - (r2 + R2)) - 4*R2*(r2 - y02);
        
        int n = SolveQuartic(coefs, ts);

        if (n == 0) return false;

        Vec3 inter;
        double t = this->get_min_t(ray, t_ray, n, ts, inter);

        if (t < min || t > hit.t) return false;

        hit.t = t;
        hit.intersection = inter;

        Vec3 t_inter = this->transform.apply_backward(hit.intersection);
        Vec3 q = Vec3(t_inter[0], t_inter[1], 0).unit_vector() * R;

        hit.normal = (hit.intersection - this->transform.apply_forward(q)).unit_vector();
        hit.is_front_face = dot(ray.direction(), hit.normal) < 0;
        hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

        return true;
    }
};
