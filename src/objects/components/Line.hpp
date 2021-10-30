#pragma once

#include "Point.hpp"
#include "Vector.hpp"

// Equation:
// x = x₀ + aλ
// y = y₀ + bλ
// z = z₀ + cλ

class Line
{
    private:
        Point p;
        Vector v;
    public:
        Line(double px, double py, double pz, double vx, double vy, double vz);
        Line(const Point &p, const Vector &v);
        Line(const Point &a, const Point &b);
        ~Line();

        Point &getP();
        Vector &getV();

        double distWith(const Point &p) const;

        Point *getPointFor(double t);
        Point *getPointAt(double dist);

        friend std::ostream& operator<< (std::ostream& out, const Line& line);
};