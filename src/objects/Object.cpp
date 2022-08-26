
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

    double ts[10];

    int n = this->get_ts(t_ray, ts);

    n = this->filter_ts(n, ts);

    if (n == 0) return false;

    Vec3 global_inter, local_inter;
    double t = this->get_min_t(ray, t_ray, n, ts, global_inter, local_inter);

    if (t < min || t > hit.t) return false;

    hit.t = t;
    hit.local_inter = local_inter;
    hit.global_inter = global_inter;
    hit.normal = this->get_normal(hit);
    hit.is_front_face = ray.direction().dot(hit.normal) < 0;
    hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

    hit.u = this->get_u(hit);
    hit.v = this->get_v(hit);

    return true;
}

int Object::filter_ts(int n, double *ts) const
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

double Object::get_min_t(const Ray &ray, const Ray &t_ray, int n, double *ts, Vec3 &global_inter, Vec3 &local_inter) const
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