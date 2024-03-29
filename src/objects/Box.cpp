
#include "Box.hpp"

Box::Box(Transform transform, Material *material, Texture *texture)
    : Object(transform, material, texture)
{}

int Box::get_ts(const Ray &t_ray, double *ts) const
{
    ts[0] = (t_ray.origin()[0] - 1) / -t_ray.direction()[0];
    ts[1] = (t_ray.origin()[0] + 1) / -t_ray.direction()[0];
    ts[2] = (t_ray.origin()[1] - 1) / -t_ray.direction()[1];
    ts[3] = (t_ray.origin()[1] + 1) / -t_ray.direction()[1];
    ts[4] = (t_ray.origin()[2] - 1) / -t_ray.direction()[2];
    ts[5] = (t_ray.origin()[2] + 1) / -t_ray.direction()[2];

    return 6;
}

Vec3 Box::get_normal(const hit_t &hit) const
{
    switch (hit.t.index)
    {
    case 0:
        return this->transform.apply_forward(Vec3(0, 0, 0)) - this->transform.apply_forward(Vec3(-1, 0, 0));
    case 1:
        return this->transform.apply_forward(Vec3(0, 0, 0)) - this->transform.apply_forward(Vec3(1, 0, 0));
    case 2:
        return this->transform.apply_forward(Vec3(0, 0, 0)) - this->transform.apply_forward(Vec3(0, -1, 0));
    case 3:
        return this->transform.apply_forward(Vec3(0, 0, 0)) - this->transform.apply_forward(Vec3(0, 1, 0));
    case 4:
        return this->transform.apply_forward(Vec3(0, 0, 0)) - this->transform.apply_forward(Vec3(0, 0, -1));
    case 5:
        return this->transform.apply_forward(Vec3(0, 0, 0)) - this->transform.apply_forward(Vec3(0, 0, 1));
    default:
        throw "Bad t.index";
    }
}

double Box::get_u(const hit_t &hit, const Ray &t_ray) const
{
    switch (hit.t.index)
    {
    case 0:
        return t_ray.origin()[2] + t_ray.direction()[2] * hit.t.local;
    case 1:
        return t_ray.origin()[2] + t_ray.direction()[2] * hit.t.local;
    case 2:
        return t_ray.origin()[2] - t_ray.direction()[2] * hit.t.local;
    case 3:
        return t_ray.origin()[2] - t_ray.direction()[2] * hit.t.local;
    case 4:
        return t_ray.origin()[0] + t_ray.direction()[0] * hit.t.local;
    case 5:
        return t_ray.origin()[0] + t_ray.direction()[0] * hit.t.local;
    default:
        throw "Bad t.index";
    }
}

double Box::get_v(const hit_t &hit, const Ray &t_ray) const
{
    switch (hit.t.index)
    {
    case 0:
        return t_ray.origin()[1] + t_ray.direction()[1] * hit.t.local;
    case 1:
        return t_ray.origin()[1] + t_ray.direction()[1] * hit.t.local;
    case 2:
        return t_ray.origin()[0] + t_ray.direction()[0] * hit.t.local;
    case 3:
        return t_ray.origin()[0] + t_ray.direction()[0] * hit.t.local;
    case 4:
        return t_ray.origin()[1] - t_ray.direction()[1] * hit.t.local;
    case 5:
        return t_ray.origin()[1] - t_ray.direction()[1] * hit.t.local;
    default:
        throw "Bad t.index";
    }
}

int Box::filter_ts(int n, t_t *ts, const Ray &t_ray) const
{
    for (int i = 0; i < n; ++i)
    {
        Vec3 local_inter = t_ray.point_at_parameter(ts[i].local);
        if (
            ts[i].local < EPSILON ||
            local_inter[0] < -1 - EPSILON || local_inter[0] > 1 + EPSILON ||
            local_inter[1] < -1 - EPSILON || local_inter[1] > 1 + EPSILON ||
            local_inter[2] < -1 - EPSILON || local_inter[2] > 1 + EPSILON
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
