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
        Line(const Point &a, double x, double y, double z);
        ~Line();

        Point &getP();
        Point getP() const;
        Vector &getV();
        Vector getV() const;

        double getX() const;
        double getY() const;
        double getZ() const;
        double getPX() const;
        double getPY() const;
        double getPZ() const;

        void normalize();
        double distWith(const Point &p) const;
        Point getPointFor(double t) const;

        friend std::ostream& operator<< (std::ostream& out, const Line& line);
};