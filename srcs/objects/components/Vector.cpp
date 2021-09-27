#include "Vector.hpp"

Vector::Vector(const double x, const double y, const double z) : x(x), y(y), z(z)
{
}

Vector::~Vector()
{
}

std::ostream& operator<< (std::ostream& out, const Vector& vector)
{
    out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
    return out;
}