#include "Cylinder.hpp"

Cylinder::Cylinder(double r) : r(r), tr()
{
    tr.updateMatrices();
}
Cylinder::~Cylinder(){}

std::vector<Intersection> Cylinder::intersect(const Line &line) const
{
    Point p1 = line.getP();
    Point p2 = line.getP().applyVector(line.getV());
    Matrix p1m(1, 4);
    p1m[0][0] = p1.getX();
    p1m[0][1] = p1.getY();
    p1m[0][2] = p1.getZ();
    p1m[0][3] = 1;

    Matrix p2m(1, 4);
    p2m[0][0] = p2.getX();
    p2m[0][1] = p2.getY();
    p2m[0][2] = p2.getZ();
    p2m[0][3] = 1;

    Matrix p1mm = this->tr.getBackwardMatrix() * p1m;
    Matrix p2mm = this->tr.getBackwardMatrix() * p2m;

    Point new_p(p1mm[0][0], p1mm[0][1], p1mm[0][2]);
    Vector new_v(p2mm[0][0] - p1mm[0][0], p2mm[0][1] - p1mm[0][1], p2mm[0][2] - p1mm[0][2]);
    new_v.normalize();

    double a, b, c;
    a = pow(new_v.getX(), 2) + pow(new_v.getY(), 2);
    b = 2 * new_p.getX() * new_v.getX() + 2 * new_p.getY() * new_v.getY();
    c = pow(new_p.getX(), 2) + pow(new_p.getY(), 2) - pow(this->r, 2);

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);

    std::vector<Intersection> intersections;
    for (double s : solutions) {
        if (s > 0.00001) {
            Matrix origin(1, 4);
            origin = this->tr.getForwardMatrix() * origin;
            Point oriii(origin[0][0], origin[0][1], origin[0][2]);
            Point p(
                new_p.getX() + s * new_v.getX(),
                new_p.getY() + s * new_v.getY(),
                new_p.getZ() + s * new_v.getZ()
            );
            Matrix tmp(1, 4);
            tmp[0][0] = p.getX();
            tmp[0][1] = p.getY();
            tmp[0][2] = p.getZ();
            tmp = this->tr.getForwardMatrix() * tmp;
            Point pp(tmp[0][0], tmp[0][1], tmp[0][2]);
            pp = pp - oriii;
            intersections.push_back(Intersection(pp, s, (Object*)this));
        }
    }
    return intersections;
}

double Cylinder::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return 0;
}

Line Cylinder::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    return Line(1, 1, 1, 1, 1, 1);
}

Color Cylinder::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    screenWidth = intersection.getX();

    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        double p = (double)((double)height / (double)screen_height);
        return Color(
            this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * p),
            this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * p),
            this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * p),
            this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * p)
        );
    } else if (this->texture.getType() == "Grid") {
        return this->getColor(((height / this->texture.getValue1()) + (width / this->texture.getValue2())) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        return this->getColor((width / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        return this->getColor((height / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "Image") {
        throw "Texture type has no power here";
    } else {
        throw "Should never happen";
    }
}