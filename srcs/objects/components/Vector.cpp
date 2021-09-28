#include "Vector.hpp"

Vector::Vector(const double x, const double y, const double z) : x(x), y(y), z(z)
{
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

std::ostream& operator<< (std::ostream& out, const Vector& vector)
{
    out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
    return out;
}