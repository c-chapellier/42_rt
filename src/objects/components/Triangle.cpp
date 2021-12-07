#include "Triangle.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3)
    : p1(p1), p2(p2), p3(p3)
{}
Triangle::Triangle(Point *p1, Point *p2, Point *p3)
    : p1(p1), p2(p2), p3(p3)
{}

Triangle::~Triangle() {}

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

Plane Triangle::getPlane() const
{
    return Plane(this->p1, this->p2, this->p3);
}

/* * * * * * * * * * * * * * * * * * * * *

*                FUNCTIONS               *

* * * * * * * * * * * * * * * * * * * * */

void Triangle::intersect(std::vector<Intersection> *intersections, const Line &l, Object *obj) const
{
    Plane plane(this->p1, this->p2, this->p3);
    double area = plane.getV().getMagnitude();

    std::vector<Intersection> tmp;
    plane.intersect(&tmp, l);

    for (Intersection inter : tmp) {
        Vector pa(inter.getRealPoint(), this->p1);
        Vector pb(inter.getRealPoint(), this->p2);
        Vector pc(inter.getRealPoint(), this->p3);
        double alpha, beta, gama;
        alpha = pb.crossProductMagnitude(pc) / area;
        beta = pc.crossProductMagnitude(pa) / area;
        gama = pa.crossProductMagnitude(pb) / area;

        if(alpha >= 0 && alpha <= 1 &&
            beta >= 0 && beta <= 1 &&
            gama >= 0 && gama <= 1 &&
            alpha + beta + gama < 1.001 && alpha + beta + gama > 0.990
        )
            intersections->push_back(Intersection(inter.getRealPoint(), inter.getLocalPoint(), inter.getDist(), obj, (Triangle*)this));
    }
}