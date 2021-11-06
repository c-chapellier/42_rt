#include "Plane.hpp"

Plane::Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz)
    : Object(), p(px, py, pz), v(vx, vy, vz)
{
}

Plane::Plane(const Point &p1, const Point &p2) : Object(), p(p1), v(p2, p1)
{}

Plane::Plane(const Point &p, const Vector &v)
    : Object(), p(p), v(v)
{
}

Plane::Plane(const Point &p, double vx, double vy, double vz)
    : Object(), p(p), v(vx, vy, vz)
{
}

Plane::Plane(const Point &p1, const Point &p2, const Point &p3) : Object(), p(p1), v(*Vector(p1, p2).crossProduct(Vector(p1, p3)))
{
}

Plane::~Plane()
{
}

Point Plane::getP() const
{
    return this->p;
}
Vector Plane::getV() const
{
    return this->v;
}

Point Plane::intersect(const Line &line) const
{
    double a, b, c, K;
    a = this->v.getX();
    b = this->v.getY();
    c = this->v.getZ();
    K = ((this->v.getX() * (this->p.getX() * -1)) + (this->v.getY() * (this->p.getY() * -1)) + (this->v.getZ() * (this->p.getZ() * -1))) * -1;
    double t, C;
    t = (a * line.getV().getX()) + (b * line.getV().getY()) + (c * line.getV().getZ());
    C = (a * line.getP().getX()) + (b * line.getP().getY()) + (c * line.getP().getZ());
    if(t == 0 && C != K){
        // no intersection
        throw "Line do not intersect the plane";
    } else if (t == 0 && C == K) {
        // the line is in the plane
        throw "Line do not intersect the plane";
    } else {
        double s1 = (K - C) / t;
        return line.getPointFor(s1);
    }
}

//          a . b
// sin θ = -------
// 
double Plane::angleWith(const Vector &v) const
{
    double d = this->v.getMagnitude() * v.getMagnitude();

    if (d == 0.0)
        std::cout << "Plane::angleWith: div by 0" << std::endl;

    return DEGREE(asin((this->v.scalarProduct(v) / d)));
}

double Plane::angleWith(const Line &line) const
{
    return this->angleWith(line.getV());
}

double Plane::angleWith(const Plane &p) const
{
    return this->v.angleWith(p.v);
}

Color Plane::getColorAt(int height, int width, int screen_height, int screenWidth, Point &intersection)
{
    screenWidth = intersection.getX();

    if (this->texture.getType() == "Uniform") {
        return getColor();
    } else if (this->texture.getType() == "Gradient") {
        double p = (double)((double)height / (double)screen_height);
        return Color(
            getColor(0).getR() + (int)((double)((double)getColor(1).getR() - (double)getColor(0).getR()) * p),
            getColor(0).getG() + (int)((double)((double)getColor(1).getG() - (double)getColor(0).getG()) * p),
            getColor(0).getB() + (int)((double)((double)getColor(1).getB() - (double)getColor(0).getB()) * p),
            getColor(0).getO() + (int)((double)((double)getColor(1).getO() - (double)getColor(0).getO()) * p)
        );
    } else if (this->texture.getType() == "Grid") {
        return getColor(((height / this->texture.getValue1()) + (width / this->texture.getValue2())) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        return getColor((width / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        return getColor((height / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "Image") {
        throw "Texture type Image ca't be apply here";
    } else {
        throw "Should never happen";
    }
}

std::ostream& operator<< (std::ostream& out, const Plane& plane)
{
    out << "Plane : {" << std::endl
    << "\tpoint : " << plane.p << std::endl
    << "\tvector : " << plane.v << std::endl
    << "}";
    return out;
}