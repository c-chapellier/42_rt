#include "Sphere.hpp"

Sphere::Sphere(const Point &p, double r) : Object(), p(p), r(r)
{

}

Sphere::Sphere(double x, double y, double z, double r) : Object(), p(x, y, z), r(r)
{

}

Sphere::Sphere(double x, double y, double z, double r, const Color &color) : Object(color), p(x, y, z), r(r)
{

}

Sphere::~Sphere(){};

Point Sphere::getP() const
{
    return this->p;
}

double Sphere::getR() const
{
    return this->r;
}

std::vector<Intersection> Sphere::intersect(const Line &line) const
{
    double a, b, c, tmp1, tmp2, tmp3;

    tmp1 = line.getP().getX() - p.getX();
    tmp2 = line.getP().getY() - p.getY();
    tmp3 = line.getP().getZ() - p.getZ();

    a = pow(line.getV().getX(), 2)
        + pow(line.getV().getY(), 2)
        + pow(line.getV().getZ(), 2);

    b = 2 * tmp1 * line.getV().getX()
        + 2 * tmp2 * line.getV().getY()
        + 2 * tmp3 * line.getV().getZ();
        
    c = pow(tmp1, 2)
        + pow(tmp2, 2)
        + pow(tmp3, 2)
        - pow(this->r, 2);

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);
    std::vector<Intersection> intersections;
    for (double s: solutions)
    {
        if (s > 0.00001)
        {
            Point tmp(
                line.getP().getX() + line.getV().getX() * s,
                line.getP().getY() + line.getV().getY() * s,
                line.getP().getZ() + line.getV().getZ() * s
            );
            intersections.push_back(Intersection(tmp, s, (Object*)this));
        }
    }
        
    return intersections;
}

double Sphere::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return Plane(intersection.getP(), this->p).angleWith(line);
}

Line Sphere::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    Vector v(this->p, intersection.getP());
    return Line(intersection.getP(), v.getReflectionOf(line.getV()));
}

Color Sphere::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    height = width;
    screenWidth = screen_height;

    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        double ratio = intersection.getZ() > this->p.getZ() ?
            (this->r - (intersection.getZ() - this->p.getZ())) / (2 * this->r) :
            (this->r + (this->p.getZ() - intersection.getZ())) / (2 * this->r);
            
        return Color(
            this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * ratio),
            this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * ratio),
            this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * ratio),
            this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * ratio)
        );
    } else if (this->texture.getType() == "Grid") {
        // value1 = rows
        // value2 = cols
        double z = intersection.getZ() - this->getP().getZ() + this->r;
        double fy = (2 * this->r) / (double)this->texture.getValue1();
        int y = (int)(z / fy);

        Point tmp(this->getP().getX(), this->getP().getY(), intersection.getZ());
        Vector v(tmp, intersection);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
        int fx = 360 / this->texture.getValue2();
        int x = alpha / fx;
        
        return this->getColor((x + y) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        if (intersection.getY() > 0)
            return this->getColor(((int)intersection.getY() / this->texture.getValue1()) % 2);
        return this->getColor((abs((int)intersection.getY() / this->texture.getValue1()) + 1) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        if (intersection.getZ() > 0)
            return this->getColor(((int)intersection.getZ() / this->texture.getValue1()) % 2);
        return this->getColor((abs((int)intersection.getZ() / this->texture.getValue1()) + 1) % 2);
    } else if (this->texture.getType() == "Image") {
        return TextureAplicator::applyTextureOnSphereAt(*this, intersection);
    } else {
        throw "Should never happen";
    }
}