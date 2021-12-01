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

Plane::Plane(const Point &p1, const Point &p2, const Point &p3)
    : Object(), p(p1), v(Vector(p1, p2).crossProduct(Vector(p1, p3)))
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

std::vector<Intersection> Plane::intersect(const Line &line) const
{
    double a = this->v.getX();
    double b = this->v.getY();
    double c = this->v.getZ();
    double K = ((a * (this->p.getX() * -1)) + (b * (this->p.getY() * -1)) + (c * (this->p.getZ() * -1))) * -1;
    double t = (a * line.getV().getX()) + (b * line.getV().getY()) + (c * line.getV().getZ());
    double C = (a * line.getP().getX()) + (b * line.getP().getY()) + (c * line.getP().getZ());
    
    std::vector<Intersection> intersections;
    if (t == 0 && C != K) {
        //throw NoInterException("Line do not intersect the plane");
    } else if (t == 0 && C == K) {
        //throw NoInterException("Line do not intersect the plane");
    } else {
        double s = (K - C) / t;
        //return line.getPointFor(s);
        if(s > 0.00001)
            intersections.push_back(Intersection(line.getPointFor(s), s, (Object*)this));
    }
    return intersections;
}

//          a . b
// sin θ = -------
// 
double Plane::angleWith(const Vector &v) const
{
    double d = this->v.getMagnitude() * v.getMagnitude();
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

double Plane::angleWithAt(const Line &line, const Intersection &intersection) const
{
    intersection.getP();
    return this->angleWith(line.getV());
}

Line Plane::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    Vector ref = v.getReflectionOf(line.getV());
    // return Line(intersection.getP(), ref);
    return Line(intersection.getP(), 
                ref.getX() + intersection.getP().getX(),
                ref.getY() + intersection.getP().getY(),
                ref.getZ() + intersection.getP().getZ());
}

Color Plane::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
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