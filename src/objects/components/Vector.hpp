#pragma once

#include <iostream>
#include <math.h>

#include "./../../headers/define.hpp"
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
        Vector(Point &p1, const Point &p2);
        Vector(Point &p, const double x, const double y, const double z);
        Vector(const double x, const double y, const double z, Point &p);
        Vector(const Vector &vector);
        Vector(const Vector &vector, double div);
        ~Vector();

        double getX();
        double getY();
        double getZ();

        double getMagnitude();
        double scalarProduct(Vector *v);
        double crossProductMagnitude(Vector *v);
        Vector *crossProduct(Vector *v);
        double angleWith(Vector *v);

        int directionXY(Vector *v);
        int directionXZ(Vector *v);
        double crossProductXY(Vector *v);
        double crossProductXZ(Vector *v);
        double scalarProductXY(Vector *v);
        double scalarProductXZ(Vector *v);

        friend std::ostream& operator<<(std::ostream& out, const Vector& vector);
};