
#include "Sphere.hpp"

Sphere::Sphere(Transform transform, Material *material, Texture *texture)
    : Object(transform, material, texture)
{
    
}

int Sphere::get_ts(const Ray &t_ray, double *ts) const
{
    double coefs[3];

    coefs[2] = t_ray.direction().squared_length();
    coefs[1] = t_ray.origin().dot(t_ray.direction());
    coefs[0] = t_ray.origin().squared_length() - 1;
        
    return EquationSolver::QuadraticSphere(coefs, ts);
}

Vec3 Sphere::get_normal(const hit_t &hit) const
{
    return (hit.global_inter - this->transform.apply_forward(Vec3(0, 0, 0))).unit_vector();
}

double Sphere::get_u(const hit_t &hit) const
{
    return atan2(hit.local_inter[0]*hit.local_inter[0] + hit.local_inter[1]*hit.local_inter[1], hit.local_inter[2]) / M_PI_2 - 1;
}

double Sphere::get_v(const hit_t &hit) const
{
    return atan2(hit.local_inter[1], hit.local_inter[0]) / M_PI;
}
