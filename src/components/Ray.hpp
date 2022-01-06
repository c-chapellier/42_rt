#pragma once

#include "../header.hpp"

class Ray
{
private:
    Vec3 A, B;
    
public:
    Ray() {}
    Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }

    Vec3 origin() const       { return A; }
    Vec3 direction() const    { return B; }
    Vec3 point_at_parameter(double t) const { return A + t*B; }
};