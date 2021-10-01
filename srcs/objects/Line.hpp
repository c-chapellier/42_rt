#pragma once

#include "components/Point.hpp"
#include "components/Vector.hpp"

// Equation:
// x = x₀ + aλ
// y = y₀ + bλ
// z = z₀ + cλ

class Line
{
    private:
        Point *p;
        Vector *v;
    public:
        Line(double px, double py, double pz, double vx, double vy, double vz);
        Line(Point p, Vector v);
        ~Line();

        Point *getP();
        Vector *getV();

        Point *getPointFor(double t);
        Point *getPointAt(double dist);

        friend std::ostream& operator<< (std::ostream& out, const Line& line);
};