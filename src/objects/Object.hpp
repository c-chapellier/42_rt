#pragma once

#include "../materials/Material.hpp"

class Object
{
public:
    Material *material;
    Transform transform;
    Texture *texture;

    Object(Transform transform, Material *material, Texture *texture)
        : material(material), transform(transform), texture(texture)
    {}
    virtual ~Object() {};
    virtual bool intersect(const Ray &ray, double min, hit_t &hit) const = 0;

    double get_min_t(const Ray &ray, const Ray &t_ray, int n, double *ts, Vec3 &global_inter, Vec3 &local_inter) const
    {
        local_inter = t_ray.point_at_parameter(ts[0]);
        global_inter = this->transform.apply_forward(local_inter);

        double t = ray.parameter_at_point(global_inter);

        for (int i = 1; i < n; ++i)
        {
            Vec3 local_inter_tmp = t_ray.point_at_parameter(ts[i]);
            Vec3 global_inter_tmp = this->transform.apply_forward(local_inter_tmp);
            double t_tmp = ray.parameter_at_point(global_inter_tmp);

            if (t_tmp < t)
            {
                t = t_tmp;
                local_inter = local_inter_tmp;
                global_inter = global_inter_tmp;
            }
        }

        return t;
    }
};
