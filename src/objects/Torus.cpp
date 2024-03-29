
#include "Torus.hpp"

Torus::Torus(Transform transform, Material *material, Texture *texture, double R, double r)
    : Object(transform, material, texture), R(R), r(r), R2(R*R), r2(r*r), r2R2(r2 + R2)
{

}

int Torus::get_ts(const Ray &t_ray, double *ts) const
{
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

    double coefs[5];

    coefs[4] = SQUARE(a2b2c2);
    coefs[3] = 4 * a2b2c2 * x0ay0bz0c;
    coefs[2] = 2 * a2b2c2 * (x02y02z02 - r2R2) + 4*SQUARE(x0ay0bz0c) + 4*R2*c2;
    coefs[1] = 4 * (x02y02z02 - r2R2) * x0ay0bz0c + 8*R2*z0c;
    coefs[0] = SQUARE(x02y02z02 - r2R2) - 4*R2*(r2 - z02);
        
    return EquationSolver::Quartic(coefs, ts);
}

Vec3 Torus::get_normal(const hit_t &hit) const
{
    Vec3 q = Vec3(hit.local_inter[0], hit.local_inter[1], 0).unit_vector() * this->R;
    return (hit.global_inter - this->transform.apply_forward(q)).unit_vector();
}

double Torus::get_u(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray;

    return -atan2(hit.local_inter[2], (sqrt(hit.local_inter[0]*hit.local_inter[0] + hit.local_inter[1]*hit.local_inter[1]) - this->R) / this->r) / M_PI;
}

double Torus::get_v(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray;
    
    return -atan2(hit.local_inter[0], hit.local_inter[1]) / M_PI;
}
