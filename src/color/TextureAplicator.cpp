#include "TextureAplicator.hpp"

Color TextureAplicator::applyTexture(Object *o, Point &intersection)
{
    Sphere *sp = dynamic_cast<Sphere*>(o);
    if(sp != NULL) {
        return applyTextureOnSphereAt(*sp, intersection);
    } else {
        throw "This type of texture is not allowed on this type of object";
    }
}

Color TextureAplicator::applyTextureOnSphereAt(const Sphere &sp, const Point &intersection)
{
    double y_ratio = intersection.getZ() >= 0 ?
            sp.getR() - intersection.getZ() :
            sp.getR() + abs(intersection.getZ());
    y_ratio /= sp.getR() * 2;

    Vector v(0, 0, 0, intersection.getX(), intersection.getY(), 0);
    Vector x_axis(0, 1, 0);
    double alpha = v.angleWith(x_axis);
    alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
    double x_ratio = alpha / 360;

    return sp.getTexture().getImageTextureAt(y_ratio, x_ratio);
}