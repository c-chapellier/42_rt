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
        Vector(const Point &p1, const Point &p2);
        Vector(const Point &p, const double x, const double y, const double z);
        Vector(const double x, const double y, const double z, const Point &p);
        Vector(const Vector &vector);
        Vector(const Vector &vector, double div);
        ~Vector();

        double getX() const;
        double getY() const;
        double getZ() const;
        double getMagnitude() const;
        Vector getNormalized() const;

        double scalarProduct(const Vector &v) const;
        double dotProduct(const Vector &v) const;
        double crossProductMagnitude(const Vector &v) const;
        Vector crossProduct(const Vector &v) const;
        double angleWith(const Vector &v) const;
        Vector getReflectionOf(const Vector &v) const;

        int directionXY(const Vector &v) const;
        int directionXZ(const Vector &v) const;
        double crossProductXY(const Vector &v) const;
        double crossProductXZ(const Vector &v) const;
        double scalarProductXY(const Vector &v) const;
        double scalarProductXZ(const Vector &v) const;

        friend std::ostream& operator<<(std::ostream& out, const Vector &vector);
};