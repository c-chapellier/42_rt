
#include "Torus.hpp"

Torus::Torus(Transform transform, Material *material, Texture *texture, double R, double r)
    : Object(transform, material, texture), R(R), r(r), R2(R*R), r2(r*r), r2R2(r2 + R2)
{

}

bool Torus::intersect(const Ray &ray, double min, hit_t &hit) const
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
    coefs[2] = 2 * a2b2c2 * (x02y02z02 - r2R2) + 4*SQUARE(x0ay0bz0c) + 4*R2*c2;
    coefs[1] = 4 * (x02y02z02 - r2R2) * x0ay0bz0c + 8*R2*z0c;
    coefs[0] = SQUARE(x02y02z02 - r2R2) - 4*R2*(r2 - z02);
        
    int n = EquationSolver::Quartic(coefs, ts);

    n = this->filter_ts(n, ts);

    if (n == 0) return false;

    Vec3 global_inter, local_inter;
    double t = this->get_min_t(ray, t_ray, n, ts, global_inter, local_inter);

    if (t < min || t > hit.t) return false;

    hit.t = t;
    hit.local_inter = local_inter;
    hit.global_inter = global_inter;

    Vec3 t_inter = this->transform.apply_backward(hit.global_inter);
    Vec3 q = Vec3(t_inter[0], t_inter[1], 0).unit_vector() * this->R;
    hit.normal = (hit.global_inter - this->transform.apply_forward(q)).unit_vector();
        
    hit.is_front_face = ray.direction().dot(hit.normal) < 0;
    hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

    hit.u = -atan2(hit.local_inter[2], (sqrt(hit.local_inter[0]*hit.local_inter[0] + hit.local_inter[1]*hit.local_inter[1]) - this->R) / this->r) / M_PI;
    hit.v = -atan2(hit.local_inter[0], hit.local_inter[1]) / M_PI;

    return true;
}
