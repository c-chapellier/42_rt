#pragma once

#include "../global.hpp"
#include "../materials/Material.hpp"
#include "../textures/Texture.hpp"
#include "../objects/Object.hpp"

class Plane : public Object
{
private:

public:
    Plane(Transform transform, Material *material, Texture *texture)
        : Object(transform, material, texture)
    {}

    bool intersect(const Ray &ray, double min, hit_t &hit) const
    {
        Ray t_ray = this->transform.apply_backward(ray);

        Vec3 normal = Vec3(1, 0, 0);
        double ts[] = { -normal.dot(t_ray.origin()) / normal.dot(t_ray.direction()) };

        Vec3 global_inter, local_inter;
        double t = this->get_min_t(ray, t_ray, 1, ts, global_inter, local_inter);

        if (t < min || t > hit.t) return false;

        hit.t = t;
        hit.local_inter = local_inter;
        hit.global_inter = global_inter;
        hit.normal = normal;
        hit.is_front_face = ray.direction().dot(hit.normal) < 0;
        hit.normal = hit.is_front_face ? hit.normal : -hit.normal;

        return true;
    }
};
