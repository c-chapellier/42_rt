#include "PlaneObj.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

PlaneObj::PlaneObj(){}
PlaneObj::~PlaneObj(){}

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void PlaneObj::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Line local_line = this->tr.apply(line, TO_LOCAL);

    if (local_line.getZ() == 0) {
        // line in the plane
    } else {
        double s = -local_line.getPZ() / local_line.getZ();
        if(s > 0.00001) {
            Point local_point(
                local_line.getPX() + s * local_line.getX(),
                local_line.getPY() + s * local_line.getY(),
                local_line.getPZ() + s * local_line.getZ()
            );
            Point real_point = this->tr.apply(local_point, TO_REAL);
            double dist = (real_point.getX() - line.getP().getX()) / line.getV().getX();
            intersections->push_back(Intersection(real_point, local_point, dist, (Object*)this));
        }
    }
}

double PlaneObj::angleWithAt(const Line &line, const Intersection &intersection) const
{
    Vector local_normal(0, 0, 1);
    Vector real_normal = this->tr.apply(local_normal, TO_REAL);
    return real_normal.angleWith(line.getV());
}

Line PlaneObj::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    Vector local_vector = this->tr.apply(line.getV(), TO_LOCAL);
    Vector local_reflexion(local_vector.getX(), local_vector.getY(), -local_vector.getZ());
    Vector real_reflexion = this->tr.apply(local_vector, TO_REAL);
    return Line(intersection.getRealPoint(), real_reflexion);
}

Color PlaneObj::getColorAt(const Point &intersection) const
{
    char type = this->texture.getType();
    if (type == UNIFORM) {
        return this->getColor();
    } else if (type == GRADIENT) {
        throw "Texture unsupported";
    } else if (type == GRID) {
        /*
            The first value of the texture is the square width
            The second value of the texture is unused
        */
        double ratio1 = intersection.getX() > 0 ?
            intersection.getX() :
            abs(intersection.getX()) + texture.getValue1();
        double ratio2 = intersection.getY() > 0 ?
            intersection.getY() :
            abs(intersection.getY()) + texture.getValue2();

        return this->getColor(((int)(ratio1 / texture.getValue1()) + (int)(ratio2 / texture.getValue2())) % 2);
    } else if (type == VERTICAL_LINED) {
        /*
            The first value of the texture is the line width
            The second value of the texture is unused
        */
        double ratio = intersection.getY() > 0 ?
            intersection.getY() :
            abs(intersection.getY()) + texture.getValue1();
        return this->getColor((int)(ratio / texture.getValue1()) % 2);
    } else if (type == HORIZONTAL_LINED) {
        /*
            The first value of the texture is the line width
            The second value of the texture is unused
        */
        double ratio = intersection.getX() > 0 ?
            intersection.getX() :
            abs(intersection.getX()) + texture.getValue1();
        return this->getColor((int)(ratio / texture.getValue1()) % 2);
    } else if (type == IMAGE) {
        return TextureAplicator::applyTextureOnPlaneAt(*this, intersection);
    } else {
        throw "Should never happen";
    }
}