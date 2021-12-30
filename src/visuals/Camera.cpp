#include "Camera.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Camera::Camera(double cx, double cy, double cz, double dx, double dy, double dz, double ux, double uy, double uz, double a)
    : coordinates(cx, cy, cz), direction(dx, dy, dz), up(ux, uy, uz), angle(a), U(1, 1, 1), V(1, 1, 1), screenCenter(0, 0, 0), height(0), width(0)
{
    if (dx == 0 && dy == 0 && dz == 0)
        throw "The camera vector can not be the null vector";
    if (ux == 0 && uy == 0 && uz == 0)
        throw "The camera vector can not be the null vector";
    if (a < 60 || a > 120)
        throw "Bad angle for camera";
}

Camera::~Camera() {}

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

Point Camera::getP() const
{
    return this->coordinates;
}

Vector Camera::getV() const
{
    return this->direction;
}

Point Camera::getPoint(int hh, int ww, bool x) const
{
    return getPoint((double)(hh - ((double)height / 2)) / height, (double)(ww - ((double)width / 2)) / width);
}

Point Camera::getPoint(double h, double w) const
{
    Point tmp = this->screenCenter + (this->U * w);
    Point res = tmp + (this->V * h);
    return res;
}

std::vector< std::vector<Point> > Camera::getScreen() const
{
    // make all the points
    std::vector< std::vector<Point> > screen;
    screen.resize(height, std::vector<Point>(width));

    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            screen[h][w] = getPoint((double)(h - (height / 2)) / (double)height, (double)(w - (width / 2)) / (double)width);
        }
    }
    return screen;
}

/* * * * * * * * * * * * * * * * * * * * *

*                SETTER                  *

* * * * * * * * * * * * * * * * * * * * */

void Camera::setX(double x)
{
    this->coordinates.setX(x);
}
void Camera::setY(double y)
{
    this->coordinates.setY(y);
}
void Camera::setZ(double z)
{
    this->coordinates.setZ(z);
}
void Camera::setV(double x, double y, double z)
{
    this->direction.setX(x);
    this->direction.setY(y);
    this->direction.setZ(z);
}

void Camera::update(const Config &config)
{
    this->direction.normalize();
    this->U = Vector::crossProduct(this->up, this->direction);
    this->U.normalize();
    this->V = Vector::crossProduct(this->U, this->direction);
    this->V.normalize();

    this->height = config.getHeight() * config.getPrecision();
    this->width = config.getWidth() * config.getPrecision();

    this->U = this->U * this->width;
    this->V = this->V * this->height;
    double L = width / tan(RADIAN(angle / 2));
    this->screenCenter = this->coordinates + (this->direction * L);
}