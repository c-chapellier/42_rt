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
        Plane(Point &p1, Point &p2, Point &p3);
        ~Plane();

        Point *getP();
        Vector *getV();

        Point *intersect(Line *line);
        double angleWith(Line *line);
        double angleWith(Vector *v);
        double angleWith(Plane *p);

        friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
};