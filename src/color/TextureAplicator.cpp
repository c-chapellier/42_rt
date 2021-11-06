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
    double z, y_ratio, x_ratio;
    z = intersection.getZ() - sp.getP().getZ();
    y_ratio = z < 0 ? (sp.getR() + abs(z)) / (2 * sp.getR()) : (sp.getR() - abs(z)) / (2 * sp.getR());

    Point tmp(sp.getP().getX(), sp.getP().getY(), intersection.getZ());
    Vector v(tmp, intersection);
    Vector x_axis(0, 1, 0);
    double alpha = v.angleWith(x_axis);
    alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
    x_ratio = alpha / 360;

    return sp.getTexture().getImageTextureAt(y_ratio, x_ratio);
}