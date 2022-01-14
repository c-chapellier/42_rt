#pragma once

#include "../header.hpp"

class Object
{
public:
    Material *material;
    Transform transform;

    Object(Transform transform, Material *material) : material(material), transform(transform) {}
    virtual ~Object() {};
    virtual bool intersect(const Ray &ray, double min, hit_t &hit) const = 0;

    double get_min_t(const Ray &ray, const Ray &t_ray, int n, double *ts, Vec3 &inter) const
    {
        inter = this->transform.apply_forward(t_ray.point_at_parameter(ts[0]));

        double t = ray.parameter_at_point(inter);

        for (int i = 1; i < n; ++i)
        {
            Vec3 inter_tmp = this->transform.apply_forward(t_ray.point_at_parameter(ts[i]));
            double t_tmp = ray.parameter_at_point(inter_tmp);

            if (t_tmp < t)
            {
                t = t_tmp;
                inter = inter_tmp;
            }
        }

        return t;
    }
};
