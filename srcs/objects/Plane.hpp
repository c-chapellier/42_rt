#pragma once

#include <iostream>

#include "components/Point.hpp"
#include "components/Vector.hpp"
#include "Object.hpp"

// Equation:
// aX + bY +cZ = K

class Plane : public Object
{
    private:
        Point *p;
        Vector *v;
    public:
        Plane(Point p, Vector v);
        Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz);
        ~Plane();

        Point *intersect(Line line);

        friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
};