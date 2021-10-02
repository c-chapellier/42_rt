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
    this->x = x - p.getX();
    this->y = y - p.getY();
    this->z = z - p.getZ();
}
Vector::Vector(const double x, const double y, const double z, Point &p)
{
    this->x = p.getX() - x;
    this->y = p.getY() - y;
    this->z = p.getZ() - z;
}

Vector::Vector(const Vector &vector) : x(vector.x), y(vector.y), z(vector.z)
{
}

Vector::Vector(const Vector &vector, double div) : x(vector.x / div), y(vector.y / div), z(vector.z / div)
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
    return (this->x * v->x) + (this->y * v->y) + (this->z * v->z);
}

double Vector::crossProduct(Vector *v)
{
    return (this->y * v->z) - (v->y * this->z) - (this->x * v->z) + (v->x * this->z) + (this->x * v->y) - (v->x * this->y);
}

//          a . b
// cos θ = -------
//         |a| |b|
double Vector::angleWith(Vector *v)
{
    return DEGREE(acos((this->scalarProduct(v) / (this->getMagnitude() * v->getMagnitude()))));
}

double Vector::scalarProductXY(Vector *v)
{
    return (this->x * v->x) + (this->y * v->y);
}

double Vector::crossProductXY(Vector *v)
{
    return (this->x * v->y) - (v->x * this->y);
}

int Vector::directionXY(Vector *v)
{
    Vector *v1 = new Vector(*this, this->getMagnitude());
    Vector *v2 = new Vector(v->getX() / v->getMagnitude(), v->getY() / v->getMagnitude(), 0);
    Vector *v1r = new Vector(v1->getY(), -v1->getX(), 0);

    double d = v1r->scalarProductXY(v2);
    return d > 0 ? CLOCK_WISE : ANTI_CLOCK_WISE;
}

double Vector::scalarProductXZ(Vector *v)
{
    return (this->x * v->x) + (this->z * v->z);
}

double Vector::crossProductXZ(Vector *v)
{
    return (this->x * v->z) - (v->x * this->z);
}

int Vector::directionXZ(Vector *v)
{
    Vector *v1 = new Vector(*this, this->getMagnitude());
    Vector *v2 = new Vector(v->getX() / v->getMagnitude(), 0, v->getZ() / v->getMagnitude());
    Vector *v1r = new Vector(v1->getZ(), 0, -v1->getX());

    double d = v1r->scalarProductXY(v2);
    return d > 0 ? CLOCK_WISE : ANTI_CLOCK_WISE;
}

std::ostream& operator<< (std::ostream& out, const Vector& vector)
{
    out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
    return out;
}