#include "Plane.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Plane::Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz)
    : p(px, py, pz), v(vx, vy, vz)
{}

Plane::Plane(const Point &p1, const Point &p2) : p(p1), v(p2, p1)
{}

Plane::Plane(const Point &p, const Vector &v)
    : p(p), v(v)
{}

Plane::Plane(const Point &p, double vx, double vy, double vz)
    : p(p), v(vx, vy, vz)
{}

Plane::Plane(const Point &p1, const Point &p2, const Point &p3)
    : p(p1), v(Vector(p1, p2).crossProduct(Vector(p1, p3)))
{}

Plane::~Plane() {}

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

Point Plane::getP() const
{
    return this->p;
}
Vector Plane::getV() const
{
    return this->v;
}

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void Plane::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    double a = this->v.getX();
    double b = this->v.getY();
    double c = this->v.getZ();
    double K = ((a * (this->p.getX() * -1)) + (b * (this->p.getY() * -1)) + (c * (this->p.getZ() * -1))) * -1;
    double t = a * line.getX() + b * line.getY() + c * line.getZ();
    double C = a * line.getPX() + b * line.getPY() + c * line.getPZ();

    if (t == 0 && C != K) {
        
    } else if (t == 0 && C == K) {
        
    } else {
        double s = (K - C) / t;
        if(s > 0.00001)
            intersections->push_back(Intersection(line.getPointFor(s), line.getPointFor(s), s, (Object*)this));
    }
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
    intersection.getRealPoint();
    return this->angleWith(line.getV());
}

Line Plane::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    Vector ref = v.getReflectionOf(line.getV());
    return Line(intersection.getRealPoint(), ref);
}

/* * * * * * * * * * * * * * * * * * * * *

*               OPERATORS                *

* * * * * * * * * * * * * * * * * * * * */

std::ostream& operator<< (std::ostream& out, const Plane& plane)
{
    out << "Plane : {" << std::endl
    << "\tpoint : " << plane.p << std::endl
    << "\tvector : " << plane.v << std::endl
    << "}";
    return out;
}