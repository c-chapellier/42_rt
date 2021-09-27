#include "Point.hpp"

Point::Point(const double x, const double y, const double z) : x(x), y(y), z(z)
{
}

Point::~Point()
{
}

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ')';
    return out;
}