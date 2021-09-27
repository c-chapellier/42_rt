#pragma once

#include <iostream>

class Point
{
    private:
        const double x;
        const double y;
        const double z;
    public:
        Point(const double x, const double y, const double z);
        ~Point();

        friend std::ostream& operator<<(std::ostream& out, const Point& point);
};