#include "Cylinder.hpp"

Cylinder::Cylinder(double r) : r(r), tr()
{
    tr.updateMatrices();
}
Cylinder::~Cylinder(){}

std::vector<Intersection> Cylinder::intersect(const Line &line) const
{
    Vector back = this->tr.apply(line.getV(), BACKWARD);
    back.normalize();

    double a, b, c;
    a = pow(back.getX(), 2) + pow(back.getY(), 2);
    b = 2 * back.getP1()->getX() * back.getX() + 2 * back.getP1()->getY() * back.getY();
    c = pow(back.getP1()->getX(), 2) + pow(back.getP1()->getY(), 2) - pow(this->r, 2);

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);

    std::vector<Intersection> intersections;
    for (double s : solutions) {
        if (s > 0.00001) {
            Point origin = this->tr.apply(Point(0, 0, 0), FORWARD);
            Point p(
                back.getP1()->getX() + s * back.getX(),
                back.getP1()->getY() + s * back.getY(),
                back.getP1()->getZ() + s * back.getZ()
            );
            Point pp = this->tr.apply(p, FORWARD);
            pp = pp - origin;
            s = (pp.getX() - line.getP().getX()) / line.getV().getX();
            intersections.push_back(Intersection(pp, s, (Object*)this));
        }
    }
    return intersections;
}

double Cylinder::angleWithAt(const Line &line, const Intersection &intersection) const
{
    // go to imaginary world
    Point tmp = this->tr.apply(intersection.getP(), BACKWARD);
    // find the point on cylinder axis
    Point h(0, 0, tmp.getZ());
    // return to real world
    Point l = this->tr.apply(h, FORWARD);
    // get the plane
    Plane pl(l, intersection.getP());
    // return the intersection
    return pl.angleWithAt(line, intersection);
}

Line Cylinder::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    return Line(1, 1, 1, 1, 1, 1);
}

Color Cylinder::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    //Point tmp = this->tr.apply(intersection, BACKWARD);
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