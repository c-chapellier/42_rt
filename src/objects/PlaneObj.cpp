#include "PlaneObj.hpp"

PlaneObj::PlaneObj(){}
PlaneObj::~PlaneObj(){}

std::vector<Intersection> PlaneObj::intersect(const Line &line) const
{
    Vector local_vector = this->tr.apply(line.getV(), TO_LOCAL);
    Vector normal(0, 0, 1);

    std::vector<Intersection> intersections;
    if (local_vector.getZ() == 0) {
        // line in the plane
    } else {
        double s = -local_vector.getP1()->getZ() / local_vector.getZ();
        if(s > 0.00001) {
            Point local_point(
                local_vector.getP1()->getX() + s * local_vector.getX(),
                local_vector.getP1()->getY() + s * local_vector.getY(),
                local_vector.getP1()->getZ() + s * local_vector.getZ()
            );
            Point real_point = this->tr.apply(local_point, TO_REAL);
            double dist = (real_point.getX() - line.getP().getX()) / line.getV().getX();
            intersections.push_back(Intersection(real_point, dist, (Object*)this));
        }
    }
    return intersections;
}

double PlaneObj::angleWithAt(const Line &line, const Intersection &intersection) const
{
    Vector normal(0, 0, 1);
    Vector local_vector = this->tr.apply(line.getV(), TO_LOCAL);
    return normal.angleWith(local_vector);
}

Line PlaneObj::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    // Vector normal(0, 0, 1);
    Vector local_vector = this->tr.apply(line.getV(), TO_LOCAL);
    // Vector local_reflexion = normal.getReflectionOf(local_vector);
    // Vector real_reflexion = this->tr.apply(local_reflexion, TO_REAL);
    // real_reflexion.setP1(intersection.getP());
    Vector local_reflexion(local_vector.getX(), local_vector.getY(), -local_vector.getZ());
    Vector real_reflexion = this->tr.apply(local_vector, TO_REAL);
    real_reflexion.setP1(intersection.getP());
    return Line(intersection.getP(), real_reflexion);
    // return Line(intersection.getP(), 1, 1, 1);
}

Color PlaneObj::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    Point local_point = this->tr.apply(intersection, TO_LOCAL);

    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "Grid") {
        /*
            The first value of the texture is the square width
            The second value of the texture is unused
        */
        double ratio1 = local_point.getX() > 0 ?
            local_point.getX() :
            abs(local_point.getX()) + texture.getValue1();
        double ratio2 = local_point.getY() > 0 ?
            local_point.getY() :
            abs(local_point.getY()) + texture.getValue2();

        return this->getColor(((int)(ratio1 / texture.getValue1()) + (int)(ratio2 / texture.getValue2())) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        /*
            The first value of the texture is the line width
            The second value of the texture is unused
        */
        double ratio = local_point.getY() > 0 ?
            local_point.getY() :
            abs(local_point.getY()) + texture.getValue1();
        return this->getColor((int)(ratio / texture.getValue1()) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        /*
            The first value of the texture is the line width
            The second value of the texture is unused
        */
        double ratio = local_point.getX() > 0 ?
            local_point.getX() :
            abs(local_point.getX()) + texture.getValue1();
        return this->getColor((int)(ratio / texture.getValue1()) % 2);
    } else if (this->texture.getType() == "Image") {
        return TextureAplicator::applyTextureOnPlaneAt(*this, local_point);
    } else {
        throw "Should never happen";
    }
}