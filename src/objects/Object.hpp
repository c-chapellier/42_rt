#pragma once

#include "../header.hpp"

class Object
{
public:
    Material *material;

    Object(Material *material) { this->material = material; }
    virtual ~Object() {};
    virtual bool intersect(const Ray &ray, double min, hit_t &hit) const = 0;
};
