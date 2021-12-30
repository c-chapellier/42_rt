#include "Point.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Point::Point()
    : x(0), y(0), z(0)
{}

Point::Point(const double x, const double y, const double z)
    : x(x), y(y), z(z)
{}

Point::Point(const Point &point)
    : x(point.x), y(point.y), z(point.z)
{}
Point::Point(Point *point)
    : x(point->x), y(point->y), z(point->z)
{}

Point::~Point() {}

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

double Point::getX() const
{
    return this->x;
}
double Point::getY() const
{
    return this->y;
}
double Point::getZ() const
{
    return this->z;
}

/* * * * * * * * * * * * * * * * * * * * *

*                SETTER                  *

* * * * * * * * * * * * * * * * * * * * */

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

/* * * * * * * * * * * * * * * * * * * * *

*                FUNCTIONS               *

* * * * * * * * * * * * * * * * * * * * */

double Point::distWith(const Point &p) const
{
    return sqrt(
        (p.x - this->x) * (p.x - this->x) + 
        (p.y - this->y) * (p.y - this->y) + 
        (p.z - this->z) * (p.z - this->z)
    );
}

/* * * * * * * * * * * * * * * * * * * * *

*              OPERATORS                 *

* * * * * * * * * * * * * * * * * * * * */

Point &Point::operator=(const Point &p)
{
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    return *this;
}
Point operator+(const Point &p, const Vector &v)
{
    Point tmp(p.x + v.getX(), p.y + v.getY(), p.z + v.getZ());
    return Point(tmp);
}

Point operator+(const Point &p1, const Point &p2)
{
    Point tmp(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
    return Point(tmp);
}
Point operator-(const Point &p1, const Point &p2)
{
    Point tmp(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
    return Point(tmp);
}

bool operator==(const Point &p1, const Point &p2)
{
    return p1.getX() == p2.getX() && p1.getY() == p2.getY() && p1.getZ() == p2.getZ();
}

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ')';
    return out;
}