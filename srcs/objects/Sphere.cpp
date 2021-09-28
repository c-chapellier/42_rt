#include "Sphere.hpp"

Sphere::Sphere(double x, double y, double z, double r) : r(r)
{
    this->color = new Color();
    this->center = new Point(x, y, z);
}

Sphere::Sphere(Point p, double r) : r(r)
{
    this->color = new Color();
    this->center = new Point(p);
}

Sphere::~Sphere()
{
    delete(this->color);
    delete(this->center);
}

std::ostream& operator<< (std::ostream& out, const Sphere& sp)
{
    out << "Sphere : {" << std::endl
    << "\tradius: " << sp.r << std::endl
    << "\tcenter: " << *sp.center << std::endl
    << '}' << std::endl;
    return out;
}

Point *Sphere::intersect(Line line)
{
    double a1, b1, a2, b2, a3, b3;
    a1 = line.getV()->getX();
    b1 = line.getP()->getX() - this->center->getX();
    a2 = line.getV()->getY();
    b2 = line.getP()->getY() - this->center->getY();
    a3 = line.getV()->getZ();
    b3 = line.getP()->getZ() - this->center->getZ();
    double a, b, c;
    a = pow(a1, 2) + pow(a2, 2) + pow(a3, 2);
    b = (2 * a1 * b1) + (2 * a2 * b2) + (2 * a3 * b3);
    c = pow(b1, 2) + pow(b2, 2) + pow(b3, 2) - pow(this->r, 2);
    double delta = pow(b, 2) - (4 * a * c);
    if (delta < 0) {
        return NULL;
    } else if (delta == 0) {
        double s1 = -b / (2 * a);
        double x1, y1, z1;
        x1 = line.getP()->getX() + (line.getV()->getX() * s1);
        y1 = line.getP()->getY() + (line.getV()->getY() * s1);
        z1 = line.getP()->getZ() + (line.getV()->getZ() * s1);
        return new Point(x1, y1, z1);
    } else {
        double s1 = (-b + sqrt(delta)) / (2 * a);
        double s2 = (-b - sqrt(delta)) / (2 * a);
        double x1, y1, z1, x2, y2, z2;
        x1 = line.getP()->getX() + (line.getV()->getX() * s1);
        y1 = line.getP()->getY() + (line.getV()->getY() * s1);
        z1 = line.getP()->getZ() + (line.getV()->getZ() * s1);
        x2 = line.getP()->getX() + (line.getV()->getX() * s2);
        y2 = line.getP()->getY() + (line.getV()->getY() * s2);
        z2 = line.getP()->getZ() + (line.getV()->getZ() * s2);
        Point *p1, *p2;
        p1 = new Point(x1, y1, z1);
        p2 = new Point(x2, y2, z2);
        if(line.getP()->distWith(*p1) < line.getP()->distWith(*p2)){
            delete(p2);
            return p1;
        } else {
            delete(p1);
            return p2;
        }
    }
}