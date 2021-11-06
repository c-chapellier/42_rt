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

Point Sphere::intersect(const Line &line) const
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

    Point res;
    bool first = true;

    for (double s: solutions)
    {
        if (s > 0)
        {
            Point tmp(
                line.getP().getX() + line.getV().getX() * s,
                line.getP().getY() + line.getV().getY() * s,
                line.getP().getZ() + line.getV().getZ() * s
            );

            if (first)
            {
                res = tmp;
                first = false;
            }
            else if (line.getP().distWith(tmp) < line.getP().distWith(res))
                res = tmp;
        }
    }

    if (first == true)
        throw NoInterException("Line do not intersect sphere");
        
    return res;
}

double Sphere::angleWith(const Line &line) const
{
    return Plane(Point(intersect(line)), this->p).angleWith(line);
}

Color Sphere::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    screenWidth = 0;

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
        return TextureAplicator::applyTextureOnSphereAt(*this, intersection);
    } else {
        throw "Should never happen";
    }
}