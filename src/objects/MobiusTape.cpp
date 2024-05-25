
#include "MobiusTape.hpp"

MobiusTape::MobiusTape(Transform transform, Material *material, Texture *texture)
    : Object(transform, material, texture), r(.5)
{

}

int MobiusTape::get_ts(const Ray &t_ray, double *ts) const
{
    double x0 = t_ray.origin()[0];
    double y00 = t_ray.origin()[1];
    double z0 = t_ray.origin()[2];

    double x02 = x0*x0;
    double y02 = y00*y00;
    double z02 = z0*z0;

    double a = t_ray.direction()[0];
    double b = t_ray.direction()[1];
    double c = t_ray.direction()[2];

    double a2 = a*a;
    double b2 = b*b;
    double c2 = c*c;

    double coefs[4];

    coefs[3] = CUBE(b) + a2*b - 2*a2*c - 2*b2*c + b*c2;
    coefs[2] = 3*y00*b2 + 2*x0*a*b + a2*y00 - 4*x0*a*c - 2*a2*z0 -4*y00*b*c - 2*b2*z0 + y00*c2 + 2*b*z0*c - 2*a*c;
    coefs[1] = 3*y02*b + x02*b + 2*x0*y00*a -2*x02*c - 4*x0*a*z0 - 2*y02*c - 4*y00*b*z0 + 2*y00*z0*c + b*z02 - 2*x0*c - 2*a*z0 - b;
    coefs[0] = CUBE(y00) + x02*y00 - 2*x02*z0 - 2*y02*z0 + y00*z02 - 2*x0*z0 - y00;

    return EquationSolver::Cubic(coefs, ts);
}

Vec3 MobiusTape::get_normal(const hit_t &hit) const
{
    Vec3 p = hit.local_inter;
    Vec3 n(
        2*p[0]*p[1] - 2*p[1] - 4*p[0]*p[2],
        p[0]*p[0] + p[2]*p[2] + 3*p[1]*p[1] - 1 -4*p[1]*p[2],
        2*p[1]*p[2] - 2*p[0] - 2*p[0]*p[0] - 2*p[1]*p[1]
    );
    return hit.global_inter - this->transform.apply_forward(hit.local_inter + n);
}

double MobiusTape::get_u(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray;

    double theta = atan2(hit.local_inter[0], hit.local_inter[1]);
    Vec3 center = Vec3(-sin(theta), -cos(theta), 0);
    Vec3 dir = hit.local_inter + center;

    double u = dir.length() / this->r;
    if (dir.angle_with(center) < M_PI_2) u = -u;

    return u;
}

double MobiusTape::get_v(const hit_t &hit, const Ray &t_ray) const
{
    (void)t_ray;

    double theta = atan2(hit.local_inter[0], hit.local_inter[1]);

    double v = -theta / M_PI;
    if (v == 1) v = 0;
    return v;
}

int MobiusTape::filter_ts(int n, t_t *ts, const Ray &t_ray) const
{
    for (int i = 0; i < n; ++i)
    {
        Vec3 local_inter = t_ray.point_at_parameter(ts[i].local);
        // Vec3 p = local_inter;
        // Vec3 normal(
        //     2*p[0]*p[1] - 2*p[1] - 4*p[0]*p[2],
        //     p[0]*p[0] + p[2]*p[2] + 3*p[1]*p[1] - 1 -4*p[1]*p[2],
        //     2*p[1]*p[2] - 2*p[0] - 2*p[0]*p[0] - 2*p[1]*p[1]
        // );

        if (
            ts[i].local < EPSILON ||
            (local_inter - Vec3(local_inter[0], local_inter[1], 0).unit_vector()).length() > this->r ||
            (local_inter[0] == 0 && local_inter[1] == 0)
            // || (fabs(local_inter[1] - local_inter[2]) < 0.1 && fabs(normal[2]) < 0.3)
        )
        {
            for (int j = i; j < n - 1; ++j)
            {
                ts[j].local = ts[j + 1].local;
                ts[j].index = ts[j + 1].index;
            }
            --n;
            --i;
        }
    }
    return n;
}
