#include "Plane.hpp"

Plane::Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz)
{
    this->color = new Color();
    this->p = new Point(px, py, pz);
    this->v = new Vector(vx, vy, vz);
}

Plane::Plane(Point p, Vector v)
{
    this->color = new Color();
    this->p = new Point(p);
    this->v = new Vector(v);
}

Plane::~Plane()
{
    delete(this->color);
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

Point *Plane::intersect(Line *line)
{
    double a, b, c, K;
    a = this->v->getX();
    b = this->v->getY();
    c = this->v->getZ();
    K = ((this->v->getX() * (this->p->getX() * -1)) + (this->v->getY() * (this->p->getY() * -1)) + (this->v->getZ() * (this->p->getZ() * -1))) * -1;
    double t, C;
    t = (a * line->getV()->getX()) + (b * line->getV()->getY()) + (c * line->getV()->getZ());
    C = (a * line->getP()->getX()) + (b * line->getP()->getY()) + (c * line->getP()->getZ());
    if(t == 0 && C != K){
        // no intersection
        return NULL;
    } else if (t == 0 && C == K) {
        // the line is in the plane
        return NULL;
    } else {
        double s1 = (K - C) / t;
        return line->getPointFor(s1);
    }
}

//          a . b
// sin θ = -------
// 
double Plane::angleWith(Vector *v)
{
    return DEGREE(asin((this->v->scalarProduct(v) / (this->v->getMagnitude() * v->getMagnitude()))));
    //return this->v->angleWith(v);
}

double Plane::angleWith(Plane *p)
{
    return this->v->angleWith(p->v);
}

std::ostream& operator<< (std::ostream& out, const Plane& plane)
{
    out << "Plane : {" << std::endl
    << "\tpoint : " << *plane.p << std::endl
    << "\vector : " << *plane.v << std::endl
    << "}";
    return out;
}