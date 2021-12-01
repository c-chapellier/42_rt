#include "Vector.hpp"

Vector::Vector(const double x, const double y, const double z)
    : x(x), y(y), z(z)
{
    this->p1 = new Point(0, 0, 0);
    this->p2 = new Point(x, y, z);
}

Vector::Vector(const Point &p1, const Point &p2)
    : x(p2.getX() - p1.getX()), y(p2.getY() - p1.getY()), z(p2.getZ() - p1.getZ())
{
    this->p1 = new Point(p1);
    this->p2 = new Point(p2);
}

Vector::Vector(const Point &p, const double x, const double y, const double z)
    : x(x - p.getX()), y(y - p.getY()), z(z - p.getZ())
{
    this->p1 = new Point(p);
    this->p2 = new Point(x, y, z);
}

Vector::Vector(const double x, const double y, const double z, const Point &p)
    : x(p.getX() - x), y(p.getY() - y), z(p.getZ() - z)
{
    this->p1 = new Point(x, y, z);
    this->p2 = new Point(p);
}

Vector::Vector(const Vector &vector)
    : x(vector.x), y(vector.y), z(vector.z)
{
    this->p1 = new Point(vector.p1);
    this->p2 = new Point(vector.p2);
}

// Vector::Vector(const Vector &vector, double div)
//     : x(vector.x / div), y(vector.y / div), z(vector.z / div)
// {
// }

Vector::~Vector()
{
    delete(p1);
    delete(p2);
}

void Vector::setX(double x)
{
    this->x = x;
}
void Vector::setY(double y)
{
    this->y = y;
}
void Vector::setZ(double z)
{
    this->z = z;
}

double Vector::getX() const
{
    return this->x;
}
double Vector::getY() const
{
    return this->y;
}
double Vector::getZ() const
{
    return this->z;
}

Point *Vector::getP1() const
{
    return this->p1;
}
Point *Vector::getP2() const
{
    return this->p2;
}

double Vector::getMagnitude() const
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

Vector Vector::getNormalized() const
{
    double magnitude = getMagnitude();
    return Vector(x / magnitude, y /magnitude, z / magnitude);
}

void Vector::normalize()
{
    double magnitude = getMagnitude();
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

double Vector::scalarProduct(const Vector &v) const
{
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

double Vector::dotProduct(const Vector &v) const
{
    return this->scalarProduct(v);
}

double Vector::crossProductMagnitude(const Vector &v) const
{
    return this->crossProduct(v).getMagnitude();
}

// return a vector perendicular to the two others
// | x y z |    | y z |     | x z |     | x y |
// ---------    -------     -------     -------
// | a b c | => | b c | x - | a c | y + | a b | z
// | d e f |    | e f |     | d f |     | d e |
Vector Vector::crossProduct(const Vector &v) const
{
    return Vector(
        (this->y * v.z) - (v.y * this->z),
        -(this->x * v.z) + (v.x * this->z),
        (this->x * v.y) - (v.x * this->y)
    );
}

//          a . b
// cos θ = -------
//         |a| |b|
double Vector::angleWith(const Vector &v) const
{
    return DEGREE(acos((this->scalarProduct(v) / (this->getMagnitude() * v.getMagnitude()))));
}

Vector Vector::getReflectionOf(const Vector &d) const
{
    double coef = (2 * d.dotProduct(*this)) / pow(getMagnitude(), 2);
    Vector tmp(coef * this->getX(), coef * this->getY(), coef * this->getZ());
    Vector res(d.getX() - tmp.getX(), d.getY() - tmp.getY(), d.getZ() - tmp.getZ());
    return res;
}

double Vector::scalarProductXY(const Vector &v) const
{
    return (this->x * v.x) + (this->y * v.y);
}

double Vector::crossProductXY(const Vector &v) const
{
    return (this->x * v.y) - (v.x * this->y);
}

int Vector::directionXY(const Vector &v) const
{
    //Vector v1(*this, this->getMagnitude());
    Vector v1(*this);
    v1.normalize();
    Vector v2(v.getX() / v.getMagnitude(), v.getY() / v.getMagnitude(), 0);
    Vector v1r(v1.getY(), -v1.getX(), 0);

    double d = v1r.scalarProductXY(v2);
    return d > 0 ? CLOCK_WISE : ANTI_CLOCK_WISE;
}

double Vector::scalarProductXZ(const Vector &v) const
{
    return (this->x * v.x) + (this->z * v.z);
}

double Vector::crossProductXZ(const Vector &v) const
{
    return (this->x * v.z) - (v.x * this->z);
}

int Vector::directionXZ(const Vector &v) const
{
    //Vector v1(*this, this->getMagnitude());
    Vector v1(*this);
    v1.normalize();
    Vector v2(v.getX() / v.getMagnitude(), 0, v.getZ() / v.getMagnitude());
    Vector v1r(v1.getZ(), 0, -v1.getX());

    double d = v1r.scalarProductXY(v2);
    return d > 0 ? CLOCK_WISE : ANTI_CLOCK_WISE;
}

double Vector::scalarProduct(const Vector &v1, const Vector &v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}
double Vector::dotProduct(const Vector &v1, const Vector &v2)
{
    return Vector::scalarProduct(v1, v2);
}
Vector Vector::crossProduct(const Vector &v1, const Vector &v2)
{
    return Vector(
        (v1.y * v2.z) - (v2.y * v1.z),
        -(v1.x * v2.z) + (v2.x * v1.z),
        (v1.x * v2.y) - (v2.x * v1.y)
    );
}

Vector &Vector::operator=(const Vector &v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    delete(this->p1);
    delete(this->p2);
    this->p1 = new Point(v.p1);
    this->p2 = new Point(v.p2);
    return *this;
}

Vector operator+(const Vector &v1, const Vector &v2){
    return Vector(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}
Vector operator-(const Vector &v1, const Vector &v2){
    return Vector(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}
Vector operator*(const Vector &v1, const Vector &v2){
    return Vector(v1.getX() * v2.getX(), v1.getY() * v2.getY(), v1.getZ() * v2.getZ());
}

Vector operator*(const Vector &v1, const double d)
{
    return Vector(v1.getX() * d, v1.getY() * d, v1.getZ() * d);
}
Vector operator*(const Vector &v1, const int d)
{
    return Vector(v1.getX() * d, v1.getY() * d, v1.getZ() * d);
}

std::ostream& operator<< (std::ostream& out, const Vector& vector)
{
    out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ')';
    return out;
}