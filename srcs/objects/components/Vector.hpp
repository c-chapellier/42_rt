#pragma once

#include <iostream>
#include <math.h>

#include "Point.hpp"

class Point;

class Vector
{
    private:
        double x;
        double y;
        double z;
    public:
        Vector(const double x, const double y, const double z);
        Vector(Point &p1, Point &p2);
        Vector(Point &p, const double x, const double y, const double z);
        Vector(const double x, const double y, const double z, Point &p);
        Vector(const Vector &vector);
        ~Vector();

        double getX();
        double getY();
        double getZ();

        double getMagnitude();
        double scalarProduct(Vector *v);
        double angleWith(Vector *v);

        friend std::ostream& operator<<(std::ostream& out, const Vector& vector);
};