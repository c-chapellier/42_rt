#pragma once

#include "../global.hpp"
#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"
#include "../objects/Object.hpp"

class MobiusTape : public Object
{
public:
    MobiusTape(Transform transform, Material *material, Texture *texture)
        : Object(transform, material, texture)
    {}

    double get_min_t(const Ray &ray, const Ray &t_ray, int n, double *ts, Vec3 &global_inter, Vec3 &local_inter) const
    {
        int j = 0;

        do
        {
            local_inter = t_ray.point_at_parameter(ts[j++]);
            global_inter = this->transform.apply_forward(local_inter);
        }
        while (j < n && local_inter.length() > 1.2);
        // while (j < n && ((local_inter[0] * local_inter[0] + local_inter[1] * local_inter[1]) > 1 || fabs(local_inter[2]) > .3));

        if (j == n) throw std::string("Nothing here");

        double t = ray.parameter_at_point(global_inter);

        for (int i = 1; i < n; ++i)
        {
            Vec3 local_inter_tmp = t_ray.point_at_parameter(ts[i]);
            Vec3 global_inter_tmp = this->transform.apply_forward(local_inter_tmp);
            double t_tmp = ray.parameter_at_point(global_inter_tmp);

            // if ((local_inter_tmp[0] * local_inter_tmp[0] + local_inter_tmp[1] * local_inter_tmp[1]) > 1 || fabs(local_inter_tmp[2]) > .3)
            if (local_inter.length() > 1.2)
                continue;

            if (t_tmp < t)
            {
                t = t_tmp;
                local_inter = local_inter_tmp;
                global_inter = global_inter_tmp;
            }
        }

        return t;
    }

    bool intersect(const Ray &ray, double min, hit_t &hit) const
    {
        Ray t_ray = this->transform.apply_backward(ray).unit_ray();

        double x0 = t_ray.origin()[0];
        double y00 = t_ray.origin()[2];
        double z0 = t_ray.origin()[1];

        double x02 = x0*x0;
        double y02 = y00*y00;
        double z02 = z0*z0;

        double a = t_ray.direction()[0];
        double b = t_ray.direction()[2];
        double c = t_ray.direction()[1];

        double a2 = a*a;
        double b2 = b*b;
        double c2 = c*c;

        double coefs[4], ts[3];

        coefs[3] = CUBE(b) + a2*b - 2*a2*c - 2*b2*c + b*c2;
        coefs[2] = 3*y00*b2 + 2*x0*a*b + a2*y00 - 4*x0*a*c - 2*a2*z0 -4*y00*b*c - 2*b2*z0 + y00*c2 + 2*b*z0*c - 2*a*c;
        coefs[1] = 3*y02*b + x02*b + 2*x0*y00*a -2*x02*c - 4*x0*a*z0 - 2*y02*c - 4*y00*b*z0 + 2*y00*z0*c + b*z02 - 2*x0*c - 2*a*z0 - b;
        coefs[0] = CUBE(y00) + x02*y00 - 2*x02*z0 - 2*y02*z0 + y00*z02 - 2*x0*z0 - y00;
        
        int n = EquationSolver::Cubic(coefs, ts);

        if (n == 0) return false;

        Vec3 global_inter, local_inter;
        double t;

        try
        {
            t = this->get_min_t(ray, t_ray, n, ts, global_inter, local_inter);
        }
        catch (const std::string &s)
        {
            return false;
        }
        
        // std::cout << "t: " << t << std::endl;

        if (t < min || t > hit.t) return false;

        // std::cout << "IN" << std::endl;

        PRINT("local_inter: " << local_inter);

        hit.t = t;
        hit.local_inter = local_inter;
        hit.global_inter = global_inter;

        hit.normal = (hit.global_inter - this->transform.apply_forward(Vec3(0, 0, 0))).unit_vector();
        
        hit.is_front_face = ray.direction().dot(hit.normal) < 0;
        hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

        return true;
    }
};
