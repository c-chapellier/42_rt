
#include "MobiusTape.hpp"

MobiusTape::MobiusTape(Transform transform, Material *material, Texture *texture)
    : Object(transform, material, texture)
{

}

bool MobiusTape::intersect(const Ray &ray, double min, hit_t &hit) const
{
    Ray t_ray = this->transform.apply_backward(ray).unit_ray();

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

    double coefs[4], ts[3];

    coefs[3] = CUBE(b) + a2*b - 2*a2*c - 2*b2*c + b*c2;
    coefs[2] = 3*y00*b2 + 2*x0*a*b + a2*y00 - 4*x0*a*c - 2*a2*z0 -4*y00*b*c - 2*b2*z0 + y00*c2 + 2*b*z0*c - 2*a*c;
    coefs[1] = 3*y02*b + x02*b + 2*x0*y00*a -2*x02*c - 4*x0*a*z0 - 2*y02*c - 4*y00*b*z0 + 2*y00*z0*c + b*z02 - 2*x0*c - 2*a*z0 - b;
    coefs[0] = CUBE(y00) + x02*y00 - 2*x02*z0 - 2*y02*z0 + y00*z02 - 2*x0*z0 - y00;

    int n = EquationSolver::Cubic(coefs, ts);

    n = this->filter_ts(n, ts, t_ray);

    if (n == 0) return false;

    Vec3 global_inter, local_inter;
    double t = this->get_min_t(ray, t_ray, n, ts, global_inter, local_inter);

    if (t < min || t > hit.t) return false;

    hit.t = t;
    hit.local_inter = local_inter;
    hit.global_inter = global_inter;
    hit.normal = hit.global_inter - this->transform.apply_forward(hit.local_inter + this->normal(local_inter));
    hit.is_front_face = ray.direction().dot(hit.normal) < 0;
    hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

    return true;
}

int MobiusTape::filter_ts(int n, double *ts, const Ray &t_ray) const
{
    for (int i = 0; i < n; ++i)
    {
        Vec3 local_inter = t_ray.point_at_parameter(ts[i]);
        if (ts[i] < EPSILON || (local_inter - Vec3(local_inter[0], local_inter[1], 0).unit_vector()).length() > .5)
        {
            for (int j = i; j < n - 1; ++j)
            {
                ts[j] = ts[j + 1];
            }
            --n;
            --i;
        }
    }
    return n;
}
    
Vec3 MobiusTape::normal(const Vec3 &p) const
{
    return Vec3(
        2*p[0]*p[1] - 2*p[1] - 4*p[0]*p[2],
        p[0]*p[0] + p[2]*p[2] + 3*p[1]*p[1] - 1 -4*p[1]*p[2],
        2*p[1]*p[2] - 2*p[0] - 2*p[0]*p[0] - 2*p[1]*p[1]
    );
}
