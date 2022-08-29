
#include "TangleCube.hpp"

TangleCube::TangleCube(Transform transform, Material *material, Texture *texture)
    : Object(transform, material, texture)
{

}

int TangleCube::get_ts(const Ray &t_ray, double *ts) const
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

    EquationFiller::nx2(coefs, x0, a0, -5);
    EquationFiller::nx2(coefs, y0, b0, -5);
    EquationFiller::nx2(coefs, z0, c0, -5);

    coefs[0] += 11.8;

    return EquationSolver::Quartic(coefs, ts);
}

Vec3 TangleCube::get_normal(const hit_t &hit) const
{
    Vec3 corner(
        hit.local_inter[0] < 0 ? -1.5 : 1.5,
        hit.local_inter[1] < 0 ? -1.5 : 1.5,
        hit.local_inter[2] < 0 ? -1.5 : 1.5
    );

    return (hit.global_inter - this->transform.apply_forward(corner)).unit_vector();
}

double TangleCube::get_u(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray, (void)hit;

    return 0;
}

double TangleCube::get_v(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray, (void)hit;
    
    return 0;
}
