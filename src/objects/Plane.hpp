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
        Point p;
        Vector v;
    public:
        Plane(const Point &p, const Vector &v);
        Plane(const Point &p, double vx, double vy, double vz);
        Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz);
        Plane(const Point &p1, const Point &p2, const Point &p3);
        ~Plane();

        Point &getP();
        Vector &getV();

        Point *intersect(const Line &line) const;
        double angleWith(const Line &line) const;
        double angleWith(const Vector &v) const;
        double angleWith(Plane *p);

        friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
};