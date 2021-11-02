#include "Sphere.hpp"

Sphere::Sphere(Point &p, double r) : Object(), p(p), r(r)
{

}
Sphere::Sphere(double x, double y, double z, double r) : Object(), p(x, y, z), r(r)
{

}
Sphere::Sphere(double x, double y, double z, double r, Color &color) : Object(color), p(x, y, z), r(r)
{

}
Sphere::~Sphere(){};

Point Sphere::getP()
{
    return this->p;
}
double Sphere::getR()
{
    return this->r;
}

Point *Sphere::intersect(const Line &line) const
{
    double a, b, c, tmp1, tmp2, tmp3;
    tmp1 = (line.getP().getX() - p.getX());
    tmp2 = (line.getP().getY() - p.getY());
    tmp3 = (line.getP().getZ() - p.getZ());
    a = pow(line.getV().getX(), 2) + 
        pow(line.getV().getY(), 2) + 
        pow(line.getV().getZ(), 2);
    b = 2 * tmp1 * line.getV().getX() +
        2 * tmp2 * line.getV().getY() +
        2 * tmp3 * line.getV().getZ();
    c = pow(tmp1, 2) +
        pow(tmp2, 2) +
        pow(tmp3, 2) -
        pow(this->r, 2);
    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);
    Point *res = NULL;
    for (double s: solutions) {
        if(s > 0) {
            Point *tmp = new Point(
                line.getP().getX() + line.getV().getX() * s,
                line.getP().getY() + line.getV().getY() * s,
                line.getP().getZ() + line.getV().getZ() * s
            );
            if (res == NULL)
                res = tmp;
            else {
                if (line.getP().distWith(*tmp) < line.getP().distWith(*res)) {
                    delete(res);
                    res = tmp;
                } else {
                    delete(tmp);
                }
            }
        }
    }
    return res;
}
double Sphere::angleWith(const Line &line) const
{
    Point *tmp = intersect(line);
    Plane plane(*tmp, this->p);
    delete(tmp);
    return plane.angleWith(line);
}