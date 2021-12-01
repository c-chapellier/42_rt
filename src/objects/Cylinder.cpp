#include "Cylinder.hpp"

Cylinder::Cylinder(double r) : r(r)
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
    Point tmp = this->tr.apply(intersection, BACKWARD);
    screenWidth = intersection.getX();

    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        // get the value of Z as absolute
        int z_value = tmp.getZ() >= 0 ?   (int)(tmp.getZ() / (double)this->texture.getValue1()) :
                                    (int)((abs(tmp.getZ())) / this->texture.getValue1());
        // get the ratio of gradient
        double gr =  (tmp.getZ() >= 0 ?    mod(tmp.getZ(), this->texture.getValue1()) :
                                        mod(abs(tmp.getZ()), this->texture.getValue1()))
                    / (double)this->texture.getValue1();
        return  (z_value % 2 == 0 ? 
                Color(
                    this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * gr),
                    this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * gr),
                    this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * gr),
                    this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * gr)
                ) :
                Color(
                    this->getColor(1).getR() + (int)((double)((double)this->getColor(0).getR() - (double)this->getColor(1).getR()) * gr),
                    this->getColor(1).getG() + (int)((double)((double)this->getColor(0).getG() - (double)this->getColor(1).getG()) * gr),
                    this->getColor(1).getB() + (int)((double)((double)this->getColor(0).getB() - (double)this->getColor(1).getB()) * gr),
                    this->getColor(1).getO() + (int)((double)((double)this->getColor(0).getO() - (double)this->getColor(1).getO()) * gr)
                )
            );
    } else if (this->texture.getType() == "Grid") {
        // Combine vertical and horizontal lined
        // horizontal
        int r = tmp.getZ() >= 0 ?   (int)(tmp.getZ() / this->texture.getValue1()) :
                                    (int)((abs(tmp.getZ()) + this->texture.getValue1()) / this->texture.getValue1());

        // vertical
        Vector v(0, 0, 0, tmp.getX(), tmp.getY(), 0);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
        double circumference = this->r * 2 * M_PI;
        double length = RADIAN(alpha) / (2 * M_PI) * circumference;
        double lineSize = circumference / (double)this->texture.getValue2();

        return this->getColor((r + (int)(length / lineSize)) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        // get the angle between intersection and x_axis
        Vector v(0, 0, 0, tmp.getX(), tmp.getY(), 0);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);

        // get the length of the line from y = 0
        double circumference = this->r * 2 * M_PI;
        double length = RADIAN(alpha) / (2 * M_PI) * circumference;
        double lineSize = circumference / (double)this->texture.getValue1();
        
        return this->getColor((int)(length / lineSize) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        // find the Z intersection
        int r = tmp.getZ() >= 0 ?   (int)(tmp.getZ() / this->texture.getValue1()) :
                                    (int)((abs(tmp.getZ()) + this->texture.getValue1()) / this->texture.getValue1());
        return this->getColor(r % 2);
    } else if (this->texture.getType() == "Image") {
        throw "Texture type has no power here";
    } else {
        throw "Should never happen";
    }
}