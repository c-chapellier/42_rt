#include "Transformer.hpp"

Transformer::Transformer(){}

double Transformer::getAngle(double x, double y)
{
    if(x == 0 && y == 0)
        return 0;
    if(x == 0 && y > 0)
        return 90;
    if(x == 0 && y < 0)
        return 270;
    double alpha = DEGREE(atan(y / x));
    if(x < 0)
        alpha += 180;
    return alpha;
}

void Transformer::translate(Point &p, const Point &off)
{
    p.setX(p.getX() + off.getX());
    p.setY(p.getY() + off.getY());
    p.setZ(p.getZ() + off.getZ());
}
void Transformer::translate(std::vector<Point> &points, const Point &off)
{
    for (int i = 0; i < (int)points.size(); ++i) {
        translate(points[i], off);
    }
}
void Transformer::translateX(Point &p, double off)
{
    p.setX(p.getX() + off);
}
void Transformer::translateX(std::vector<Point> &points, double off)
{
    for (int i = 0; i < (int)points.size(); ++i) {
        translateX(points[i], off);
    }
}
void Transformer::translateY(Point &p, double off)
{
    p.setY(p.getY() + off);
}
void Transformer::translateY(std::vector<Point> &points, double off)
{
    for (int i = 0; i < (int)points.size(); ++i) {
        translateY(points[i], off);
    }
}
void Transformer::translateZ(Point &p, double off)
{
    p.setZ(p.getZ() + off);
}
void Transformer::translateZ(std::vector<Point> &points, double off)
{
    for (int i = 0; i < (int)points.size(); ++i) {
        translateZ(points[i], off);
    }
}

void Transformer::rotateAroundX(Point &p, double alpha)
{
    double dist = sqrt(pow(p.getY(), 2) + pow(p.getZ(), 2));
    double beta = getAngle(p.getY(), p.getZ());
    double gama = beta + alpha;
    p.setZ(dist * sin(RADIAN(gama)));
    p.setY(dist * cos(RADIAN(gama)));
}
void Transformer::rotateAroundX(std::vector<Point> &points, double alpha)
{
    for (int i = 0; i < (int)points.size(); ++i) {
        rotateAroundX(points[i], alpha);
    }
}
void Transformer::rotateAroundY(Point &p, double alpha)
{
    double dist = sqrt(pow(p.getX(), 2) + pow(p.getZ(), 2));
    double beta = getAngle(p.getX(), p.getZ());
    double gama = beta + alpha;
    p.setX(dist * cos(RADIAN(gama)));
    p.setZ(dist * sin(RADIAN(gama)));
}
void Transformer::rotateAroundY(std::vector<Point> &points, double alpha)
{
    for (int i = 0; i < (int)points.size(); ++i) {
        rotateAroundY(points[i], alpha);
    }
}
void Transformer::rotateAroundZ(Point &p, double alpha)
{
    double dist = sqrt(pow(p.getX(), 2) + pow(p.getY(), 2));
    double beta = getAngle(p.getX(), p.getY());
    double gama = beta + alpha;
    p.setX(dist * cos(RADIAN(gama)));
    p.setY(dist * sin(RADIAN(gama)));
}
void Transformer::rotateAroundZ(std::vector<Point> &points, double alpha)
{
    for (int i = 0; i < (int)points.size(); ++i) {
        rotateAroundZ(points[i], alpha);
    }
}