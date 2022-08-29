
#include "DupinCyclide.hpp"

DupinCyclide::DupinCyclide(Transform transform, Material *material, Texture *texture, double a, double b, double c, double d)
    : Object(transform, material, texture), a(a), b(b), c(c), d(d)
{

}

int DupinCyclide::get_ts(const Ray &t_ray, double *ts) const
{
    double x0 = t_ray.origin()[0];
    double y0 = t_ray.origin()[1];
    double z0 = t_ray.origin()[2];

    double a0 = t_ray.direction()[0];
    double b0 = t_ray.direction()[1];
    double c0 = t_ray.direction()[2];

    double coefs[5] = { 0 };

    EquationFiller::x4(coefs, x0, a0);
    EquationFiller::x4(coefs, y0, b0);
    EquationFiller::x4(coefs, z0, c0);

    EquationFiller::nx2y2(coefs, x0, y0, a0, b0, 2);
    EquationFiller::nx2y2(coefs, x0, z0, a0, c0, 2);
    EquationFiller::nx2y2(coefs, y0, z0, b0, c0, 2);

    EquationFiller::nx2(coefs, x0, a0, 2*b*b);
    EquationFiller::nx2(coefs, y0, b0, 2*b*b);
    EquationFiller::nx2(coefs, z0, c0, 2*b*b);

    EquationFiller::nx2(coefs, x0, a0, -2*d*d);
    EquationFiller::nx2(coefs, y0, b0, -2*d*d);
    EquationFiller::nx2(coefs, z0, c0, -2*d*d);

    EquationFiller::nx2(coefs, x0, a0, -4*a*a);
    EquationFiller::nx2(coefs, y0, b0, -4*b*b);

    EquationFiller::nx(coefs, x0, a0, 8*a*c*d);

    coefs[0] += -4*SQUARE(c*d) + QUARTIC(b) + QUARTIC(d) - 2*SQUARE(b*d);

    return EquationSolver::Quartic(coefs, ts);
}

Vec3 DupinCyclide::get_normal(const hit_t &hit) const
{
    double theta = atan2(hit.local_inter[0], hit.local_inter[1]);
    double length = sqrt(a*a*SQUARE(cos(theta)) + b*b*SQUARE(sin(theta)));
    Vec3 q = Vec3(hit.local_inter[0], hit.local_inter[1], 0).unit_vector() * length;
    return (hit.global_inter - this->transform.apply_forward(q)).unit_vector();
}

double DupinCyclide::get_u(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray, (void)hit;

    double theta = atan2(hit.local_inter[0], hit.local_inter[1]);
    double length = sqrt(a*a*SQUARE(cos(theta)) + b*b*SQUARE(sin(theta)));

    return -atan2(hit.local_inter[2], (sqrt(SQUARE(hit.local_inter[0]) + SQUARE(hit.local_inter[1])) - length) / this->a) / M_PI;
}

double DupinCyclide::get_v(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray, (void)hit;
    
    return -atan2(hit.local_inter[0], hit.local_inter[1]) / M_PI;
}
