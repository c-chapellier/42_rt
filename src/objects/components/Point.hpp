#pragma once

#include <iostream>
#include <math.h>

#include "Vector.hpp"
#include "./../../headers/define.hpp"

class Vector;

class Point
{
    private:
        double x;
        double y;
        double z;
    public:
        Point();
        Point(const double x, const double y, const double z);
        Point(const Point &point);
        Point(Point *point);
        ~Point();

        double getX() const;
        double getY() const;
        double getZ() const;

        void setX(double x);
        void setY(double y);
        void setZ(double z);

        double distWith(const Point &p) const;

        Point &operator=(const Point &p);
        friend Point operator+(const Point &p, const Vector &v);
        friend Point operator+(const Point &p1, const Point &p2);
        friend Point operator-(const Point &p1, const Point &p2);
        friend bool operator==(const Point &p1, const Point &p2);
        friend std::ostream& operator<<(std::ostream& out, const Point& point);
};