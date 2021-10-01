#include "Vector.hpp"

Vector::Vector(const double x, const double y, const double z) : x(x), y(y), z(z)
{
}

Vector::Vector(Point &p1, Point &p2)
{
    this->x = p2.getX() - p1.getX();
    this->y = p2.getY() - p1.getY();
    this->z = p2.getZ() - p1.getZ();
}

Vector::Vector(Point &p, const double x, const double y, const double z)
{
    this->x = p.getX() - x;
    this->y = p.getY() - y;
    this->z = p.getZ() - z;
}
Vector::Vector(const double x, const double y, const double z, Point &p)
{
    this->x = x - p.getX();
    this->y = y - p.getY();
    this->z = z - p.getZ();
}

Vector::Vector(const Vector &vector) : x(vector.x), y(vector.y), z(vector.z)
{
}

Vector::~Vector()
{
}

double Vector::getX()
{
    return this->x;
}
double Vector::getY()
{
    return this->y;
}
double Vector::getZ()
{
    return this->z;
}

double Vector::getMagnitude()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

double Vector::scalarProduct(Vector *v)
{
    return (this->x * v->x) + (this->y * v->y) + (this->y * v->y);
}

//          a . b
// cos θ = -------
//         |a| |b|
double Vector::angleWith(Vector *v)
{
    return DEGREE(acos((this->scalarProduct(v) / (this->getMagnitude() * v->getMagnitude()))));
}

std::ostream& operator<< (std::ostream& out, const Vector& vector)
{
    out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
    return out;
}