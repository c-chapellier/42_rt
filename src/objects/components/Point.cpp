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

double Point::distWith(const Point &p) const
{
    return sqrt(pow(p.x - this->x, 2) + pow(p.y - this->y, 2) + pow(p.z - this->z, 2));
}

Point *Point::applyVector(const Vector &vector) const
{
    return new Point(this->x + vector.getX(), this->y + vector.getY(), this->z + vector.getZ());
}

Point *Point::rotateAroundX(double alpha)
{
    double dist, beta, new_angle, new_y, new_z;
    Point p(this->x, 0, 0);
    Vector v(p, *this);
    Vector y_axis(0, 1, 0);
    // current polar coordinates
    dist = this->distWith(p);
    beta = v.angleWith(y_axis);
    beta = v.directionXY(y_axis) == CLOCK_WISE ? (360 - beta) : (beta); // if right turn angle = one complete turn minus himself (trigonometric circle)

    // new polar coordinates
    new_angle = mod(beta + alpha, 360);
                
    // new coordinates
    new_y = cos(RADIAN(new_angle)) * dist;
    new_z = sin(RADIAN(new_angle)) * dist;
    new_y = new_angle <= 90 ? (pos(new_y)) : new_angle <= 270 ? (neg(new_y)) : (pos(new_y));
    new_z = new_angle <= 180 ? (pos(new_z)) : (neg(new_z));
    
    return new Point(this->x, new_y, new_z);
}

Point *Point::rotateAroundY(double alpha)
{
    double dist, beta, new_angle, new_x, new_z;
    Point p(0, this->y, 0);
    Vector v(p, *this);
    Vector x_axis(1, 0, 0);
    // current polar coordinates
    dist = this->distWith(p);
    beta = v.angleWith(x_axis);
    beta = v.directionXY(x_axis) == CLOCK_WISE ? (360 - beta) : (beta); // if right turn angle = one complete turn minus himself (trigonometric circle)

    // new polar coordinates
    new_angle = mod(beta + alpha, 360);
                
    // new coordinates
    new_x = cos(RADIAN(new_angle)) * dist;
    new_z = sin(RADIAN(new_angle)) * dist;
    new_x = new_angle <= 90 ? (pos(new_x)) : new_angle <= 270 ? (neg(new_x)) : (pos(new_x));
    new_z = new_angle <= 180 ? (pos(new_z)) : (neg(new_z));

    return new Point(new_x, this->y, new_z);
}

Point *Point::rotateAroundZ(double alpha)
{
    double dist, beta, new_angle, new_x, new_y;
    Point p(0, 0, this->z);
    Vector v(p, *this);
    Vector x_axis(1, 0, 0);
    // current polar coordinates
    dist = this->distWith(p);
    beta = v.angleWith(x_axis);
    beta = v.directionXY(x_axis) == CLOCK_WISE ? (360 - beta) : (beta); // if right turn angle = one complete turn minus himself (trigonometric circle)

    // new polar coordinates
    new_angle = mod(beta + alpha, 360);
                
    // new coordinates
    new_x = cos(RADIAN(new_angle)) * dist;
    new_y = sin(RADIAN(new_angle)) * dist;
    new_x = new_angle <= 90 ? (pos(new_x)) : new_angle <= 270 ? (neg(new_x)) : (pos(new_x));
    new_y = new_angle <= 180 ? (neg(new_y)) : (pos(new_y));

    return new Point(new_x, new_y, this->z);
}

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ')';
    return out;
}

