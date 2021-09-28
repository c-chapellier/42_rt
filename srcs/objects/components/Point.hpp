#pragma once

#include <iostream>
#include <math.h>

class Point
{
    private:
        const double x;
        const double y;
        const double z;
    public:
        Point(const double x, const double y, const double z);
        Point(const Point &point);
        ~Point();

        double getX();
        double getY();
        double getZ();

        double distWith(Point p);

        friend std::ostream& operator<<(std::ostream& out, const Point& point);
};