#pragma once

#include "../materials/Material.hpp"

class Object
{
protected:
    int filter_ts(int n, double *ts) const
    {
        for (int i = 0; i < n; ++i)
        {
            if (ts[i] < EPSILON)
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

    double get_min_t(const Ray &ray, const Ray &t_ray, int n, double *ts, Vec3 &global_inter, Vec3 &local_inter) const
    {
        double t = INFINITY;

        for (int i = 0; i < n; ++i)
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

public:
    Material *material;
    Transform transform;
    Texture *texture;

    Object(Transform transform, Material *material, Texture *texture)
        : material(material), transform(transform), texture(texture)
    {}
    virtual ~Object() {};
    virtual bool intersect(const Ray &ray, double min, hit_t &hit) const = 0;
};
