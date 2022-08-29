
#include "FresnelElasticitySurface.hpp"

FresnelElasticitySurface::FresnelElasticitySurface(Transform transform, Material *material, Texture *texture, double a, double b, double c)
    : Object(transform, material, texture), a(a), b(b), c(c)
{

}

int FresnelElasticitySurface::get_ts(const Ray &t_ray, double *ts) const
{
    double x0 = t_ray.origin()[0];
    double y0 = t_ray.origin()[1];
    double z0 = t_ray.origin()[2];

    double a0 = t_ray.direction()[0];
    double b0 = t_ray.direction()[1];
    double c0 = t_ray.direction()[2];

    double coefs[5];

    // coefs[4] = QUARTIC(a0) + QUARTIC(b0) + QUARTIC(c0);
    // coefs[3] = 4*CUBE(a0)*x0 + 4*CUBE(b0)*y0 + 4*CUBE(c0)*z0;
    // coefs[2] = 6*SQUARE(a0)*SQUARE(x0) + 6*SQUARE(b0)*SQUARE(y0) + 6*SQUARE(c0)*SQUARE(z0) - SQUARE(a0)*SQUARE(a) - SQUARE(b0)*SQUARE(b) - SQUARE(c0)*SQUARE(c);
    // coefs[1] = 4*a0*CUBE(x0) + 4*b0*CUBE(y0) + 4*c0*CUBE(z0) - SQUARE(a)*2*a0*x0 - SQUARE(b)*2*b0*z0 - SQUARE(c)*2*c0*z0;
    // coefs[0] = QUARTIC(x0) + QUARTIC(y0) + QUARTIC(z0) - SQUARE(a)*SQUARE(x0) - SQUARE(b)*SQUARE(y0) - SQUARE(c)*SQUARE(z0);

    EquationFiller::x4(coefs, x0, a0);
    EquationFiller::x4(coefs, y0, b0);
    EquationFiller::x4(coefs, z0, c0);

    EquationFiller::nx2y2(coefs, x0, y0, a0, b0, 2);
    EquationFiller::nx2y2(coefs, x0, z0, a0, c0, 2);
    EquationFiller::nx2y2(coefs, y0, z0, b0, c0, 2);

    EquationFiller::nx2(coefs, x0, a0, -a*a);
    EquationFiller::nx2(coefs, y0, b0, -b*b);
    EquationFiller::nx2(coefs, z0, c0, -c*c);

    return EquationSolver::Quartic(coefs, ts);
}

Vec3 FresnelElasticitySurface::get_normal(const hit_t &hit) const
{
    return Vec3(1, 0, 0);
}

double FresnelElasticitySurface::get_u(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray, (void)hit;

    return 0;
}

double FresnelElasticitySurface::get_v(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray, (void)hit;
    
    return 0;
}
