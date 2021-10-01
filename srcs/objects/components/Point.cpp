#include "Point.hpp"

Point::Point(): x(0), y(0), z(0)
{

}

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

void Point::setX(double x)
{
    this->x = x;
}
void Point::setY(double y)
{
    this->y = y;
}
void Point::setZ(double z)
{
    this->z = z;
}

double Point::distWith(Point p)
{
    return sqrt(pow(p.x - this->x, 2) + pow(p.y - this->y, 2) + pow(p.z - this->z, 2));
}

Point *Point::applyVector(Vector *vector)
{
    return new Point(this->x + vector->getX(), this->y + vector->getY(), this->z + vector->getZ());
}

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ')';
    return out;
}

