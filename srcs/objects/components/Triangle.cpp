#include "Triangle.hpp"

Triangle::Triangle(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z, double p3x, double p3y, double p3z)
{
    this->p1 = new Point(p1x, p1y, p1z);
    this->p2 = new Point(p2x, p2y, p2z);
    this->p3 = new Point(p3x, p3y, p3z);
}
Triangle::Triangle(Point *p1, Point *p2, Point *p3)
{
    this->p1 = new Point(*p1);
    this->p2 = new Point(*p2);
    this->p3 = new Point(*p3);
}
Triangle::Triangle(Point &p1, Point &p2, Point &p3)
{
    this->p1 = new Point(p1);
    this->p2 = new Point(p2);
    this->p3 = new Point(p3);
}
Triangle::~Triangle(){
    delete(this->p1);
    delete(this->p2);
    delete(this->p3);
}

Point *Triangle::getP1()
{
    return this->p1;
}
Point *Triangle::getP2()
{
    return this->p2;
}
Point *Triangle::getP3()
{
    return this->p3;
}

Plane *Triangle::getPlane()
{
    return new Plane(*this->p1, *this->p2, *this->p3);
}

Point *Triangle::intersect(Line *l)
{
    Plane *plane = this->getPlane();
    double area = plane->getV()->getMagnitude() / 2;
    Point *p = plane->intersect(l);
    delete(plane);

    if(!p)
        return NULL;

    Vector pa(*p, *this->p1);
    Vector pb(*p, *this->p2);
    Vector pc(*p, *this->p3);
    double alpha, beta, gama;
    alpha = pb.crossProductMagnitude(&pc) / (2 * area);
    beta = pc.crossProductMagnitude(&pa) / (2 * area);
    gama = 1 - alpha - beta;

    // std::cout << alpha << " " << beta << " " << gama << std::endl;

    if(alpha >= 0 && alpha <= 1 &&
        beta >= 0 && beta <= 1 &&
        gama >= 0 && gama <= 1 &&
        alpha + beta + gama < 1.001 && alpha + beta + gama > 0.990)
        return p;
    delete(p);
    return NULL;
    
}