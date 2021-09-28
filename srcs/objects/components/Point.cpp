#include "Point.hpp"

Point::Point(const double x, const double y, const double z) : x(x), y(y), z(z)
{
}

Point::Point(const Point &point) : x(point.x), y(point.y), z(point.z)
{
}

Point::~Point()
{
}

double Point::getX()
{
    return this->x;
}
double Point::getY()
{
    return this->y;
}
double Point::getZ()
{
    return this->z;
}

double Point::distWith(Point p)
{
    return sqrt(pow(p.x - this->x, 2) + pow(p.y - this->y, 2) + pow(p.z - this->z, 2));
}

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ')';
    return out;
}

