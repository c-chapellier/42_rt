#pragma once

#include <iostream>

#include "components/Point.hpp"
#include "components/Vector.hpp"

class Plane
{
    private:
        Point *p;
        Vector *v;
    public:
        Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz);
        ~Plane();

        friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
};