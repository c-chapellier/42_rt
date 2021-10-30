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
        ~Point();

        double getX() const;
        double getY() const;
        double getZ() const;


        void setX(double x);
        void setY(double y);
        void setZ(double z);

        double distWith(const Point &p) const;
        Point *applyVector(Vector *vector);
        Point *rotateAroundX(double alpha);
        Point *rotateAroundY(double alpha);
        Point *rotateAroundZ(double alpha);

        friend std::ostream& operator<<(std::ostream& out, const Point& point);
};