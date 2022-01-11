#pragma once

#include "../header.hpp"

class Ray
{
private:
    Vec3 a, b, ab;
    
public:
    Ray() {}
    Ray(const Vec3 &a, const Vec3 &b) : a(a), b(b), ab(b - a) {}

    Vec3 origin() const { return this->a; }
    Vec3 end() const { return this->b; }
    Vec3 direction() const { return this->ab; }
    Ray unit_ray() const { return Ray(this->a, this->a + this->ab.unit_vector()); }
    Vec3 point_at_parameter(double t) const { return this->a + this->ab * t; }

    // assumes p is on the line
    double parameter_at_point(const Vec3 &p) const {
        return ((p - this->a) / this->ab)[0];
    }
};