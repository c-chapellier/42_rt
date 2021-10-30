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
        Plane(Point *p, double vx, double vy, double vz);
        Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz);
        Plane(const Point &p1, const Point &p2, const Point &p3);
        ~Plane();

        Point *getP();
        Vector *getV();

        Point *intersect(const Line &line) const;
        double angleWith(Line *line);
        double angleWith(Vector *v);
        double angleWith(Plane *p);

        friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
};