#include "Polygone.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Polygone::Polygone(std::vector<Triangle*> triangles) : Object(), triangles(triangles)
{
    if (triangles.size() == 0)
        throw "Can not create a polygone without any triangle";
}

Polygone::~Polygone()
{
    for(unsigned long i = 0; i < triangles.size(); ++i) {
        delete(triangles[i]);
    }
}

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void Polygone::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    for (unsigned long i = 0; i < this->triangles.size(); ++i) {
        triangles[i]->intersect(intersections, line, (Object*)this);
    }
}

double Polygone::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return intersection.getTr()->getPlane().angleWith(line.getV());
}

Line Polygone::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    return intersection.getTr()->getPlane().getReflectedRayAt(intersection, line);
}

Color Polygone::getColorAt(const Point &intersection) const
{
    if (this->texture.getType() == UNIFORM) {
        return this->getColor();
    } else {
        throw "Texture unsupported";
    }
}