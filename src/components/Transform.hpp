#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Matrix.hpp"

class Transform
{
private:
    Matrix a, a_inverse;

public:
    Transform(const Vec3 &translation, const Vec3 &rotation, const Vec3 &scale);
    Vec3 apply_forward(const Vec3 &p) const;
    Ray apply_forward(const Ray &ray) const;
    Vec3 apply_backward(const Vec3 &p) const;
    Ray apply_backward(const Ray &ray) const;
};
