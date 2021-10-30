#include "Plane.hpp"

Plane::Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz) : Object()
{
    this->p = new Point(px, py, pz);
    this->v = new Vector(vx, vy, vz);
}

Plane::Plane(Point p, Vector v) : Object()
{
    this->p = new Point(p);
    this->v = new Vector(v);
}

Plane::Plane(Point *p, double vx, double vy, double vz) : Object()
{
    this->p = new Point(*p);
    this->v = new Vector(vx, vy, vz);
}

Plane::Plane(const Point &p1, const Point &p2, const Point &p3) : Object()
{
    Vector v1(p1, p2);
    Vector v2(p1, p3);

    this->v = v1.crossProduct(v2);
    this->p = new Point(p1);
}

Plane::~Plane()
{
    delete(this->p);
    delete(this->v);
}

Point *Plane::getP()
{
    return this->p;
}
Vector *Plane::getV()
{
    return this->v;
}

Point *Plane::intersect(const Line &line) const
{
    double a, b, c, K;
    a = this->v->getX();
    b = this->v->getY();
    c = this->v->getZ();
    K = ((this->v->getX() * (this->p->getX() * -1)) + (this->v->getY() * (this->p->getY() * -1)) + (this->v->getZ() * (this->p->getZ() * -1))) * -1;
    double t, C;
    t = (a * line.getV().getX()) + (b * line.getV().getY()) + (c * line.getV().getZ());
    C = (a * line.getP().getX()) + (b * line.getP().getY()) + (c * line.getP().getZ());
    if(t == 0 && C != K){
        // no intersection
        return NULL;
    } else if (t == 0 && C == K) {
        // the line is in the plane
        return NULL;
    } else {
        double s1 = (K - C) / t;
        return line.getPointFor(s1);
    }
}

//          a . b
// sin θ = -------
// 
double Plane::angleWith(Vector *v)
{
    return DEGREE(asin((this->v->scalarProduct(*v) / (this->v->getMagnitude() * v->getMagnitude()))));
    //return this->v->angleWith(v);
}

double Plane::angleWith(Line *line)
{
    return this->angleWith(&line->getV());
}

double Plane::angleWith(Plane *p)
{
    return this->v->angleWith(*p->v);
}

std::ostream& operator<< (std::ostream& out, const Plane& plane)
{
    out << "Plane : {" << std::endl
    << "\tpoint : " << *plane.p << std::endl
    << "\tvector : " << *plane.v << std::endl
    << "}";
    return out;
}