#include "Triangle.hpp"

Triangle::Triangle(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z, double p3x, double p3y, double p3z)
    : p1(p1x, p1y, p1z), p2(p2x, p2y, p2z), p3(p3x, p3y, p3z)
{
}

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3)
    : p1(p1), p2(p2), p3(p3)
{
}

Triangle::Triangle(const Triangle &triangle)
    : p1(triangle.p1), p2(triangle.p2), p3(triangle.p3)
{
}

Triangle::~Triangle()
{
}

Point &Triangle::getP1()
{
    return this->p1;
}

Point &Triangle::getP2()
{
    return this->p2;
}

Point &Triangle::getP3()
{
    return this->p3;
}

Plane Triangle::getPlane() const
{
    return Plane(this->p1, this->p2, this->p3);
}

Point Triangle::intersect(const Line &l) const
{
    Plane plane(this->p1, this->p2, this->p3);
    double area = plane.getV().getMagnitude() / 2;
    Point p = plane.intersect(l);

    Vector pa(p, this->p1);
    Vector pb(p, this->p2);
    Vector pc(p, this->p3);
    double alpha, beta, gama;
    alpha = pb.crossProductMagnitude(pc) / (2 * area);
    beta = pc.crossProductMagnitude(pa) / (2 * area);
    gama = pa.crossProductMagnitude(pb) / (2 * area);

    // std::cout << alpha << " " << beta << " " << gama << std::endl;

    if(alpha >= 0 && alpha <= 1 &&
        beta >= 0 && beta <= 1 &&
        gama >= 0 && gama <= 1 &&
        alpha + beta + gama < 1.001 && alpha + beta + gama > 0.990)
        return p;
    throw "Line do not intersect the triangle";
}