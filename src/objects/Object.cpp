
#include "Object.hpp"

Object::Object(Transform transform, Material *material, Texture *texture) :
    transform(transform), material(material), texture(texture)
{
    
}

Object::~Object()
{
    delete this->material;
    delete this->texture;
}

bool Object::intersect(const Ray &ray, double min, hit_t &hit) const
{
    Ray t_ray = this->transform.apply_backward(ray).unit_ray();

    t_t ts[10];
    double ts2[10];

    int n = this->get_ts(t_ray, ts2);

    for (int i = 0; i < n; ++i)
    {
        ts[i].local = ts2[i];
        ts[i].index = i;
    }

    n = this->filter_ts(n, ts, t_ray);

    if (n == 0) return false;

    Vec3 global_inter, local_inter;
    t_t t = this->get_min_t(ray, t_ray, n, ts, global_inter, local_inter);

    if (t.global < min || t.global > hit.t.global) return false;

    hit.t = t;
    hit.local_inter = local_inter;
    hit.global_inter = global_inter;
    hit.normal = this->get_normal(hit);
    hit.is_front_face = ray.direction().dot(hit.normal) < 0;
    hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

    hit.u = this->get_u(hit, t_ray);
    hit.v = this->get_v(hit, t_ray);

    return true;
}

int Object::filter_ts(int n, t_t *ts, const Ray &t_ray) const
{
    (void)t_ray;

    for (int i = 0; i < n; ++i)
    {
        if (ts[i].local < EPSILON)
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

t_t Object::get_min_t(const Ray &ray, const Ray &t_ray, int n, t_t *ts, Vec3 &global_inter, Vec3 &local_inter) const
{
    t_t t = { INFINITY, INFINITY, -1 };

    for (int i = 0; i < n; ++i)
    {
        Vec3 local_inter_tmp = t_ray.point_at_parameter(ts[i].local);
        Vec3 global_inter_tmp = this->transform.apply_forward(local_inter_tmp);
        double global_t = ray.parameter_at_point(global_inter_tmp);

        if (global_t < t.global)
        {
            t.global = global_t;
            t.local = ts[i].local;
            t.index = ts[i].index;
            local_inter = local_inter_tmp;
            global_inter = global_inter_tmp;
        }
    }

    return t;
}