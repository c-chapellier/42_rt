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

        void setX(double x);
        void setY(double y);
        void setZ(double z);

        double getX() const;
        double getY() const;
        double getZ() const;
        double getMagnitude() const;
        Vector getNormalized() const;

        void normalize();

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

        static double scalarProduct(const Vector &v1, const Vector &v2);
        static double dotProduct(const Vector &v1, const Vector &v2);
        static Vector crossProduct(const Vector &v1, const Vector &v2);

        Vector &operator=(const Vector &v);
        friend Vector operator+(const Vector &v1, const Vector &v2);
        friend Vector operator-(const Vector &v1, const Vector &v2);
        friend Vector operator*(const Vector &v1, const Vector &v2);

        friend Vector operator*(const Vector &v1, const double d);
        friend Vector operator*(const Vector &v1, const int d);

        friend std::ostream& operator<<(std::ostream& out, const Vector &vector);
};