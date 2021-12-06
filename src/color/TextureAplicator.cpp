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

Color TextureAplicator::applyTextureOnCylinderAt(const Cylinder &cl, const Point &intersection)
{
    int imgH = cl.getTexture().getImgHeight();

    double y_ratio = intersection.getZ() >= 0 ?
            intersection.getZ() :
            (double)imgH - abs(intersection.getZ());
    y_ratio = fmin(mod(y_ratio, imgH) / imgH, 1);

    Vector v(0, 0, 0, intersection.getX(), intersection.getY(), 0);
    Vector x_axis(0, 1, 0);
    double alpha = v.angleWith(x_axis);
    alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
    double x_ratio = fmin(alpha / 360, 1);

    return cl.getTexture().getImageTextureAt(y_ratio, x_ratio);
}

Color TextureAplicator::applyTextureOnConeAt(const Cone &cn, const Point &intersection)
{
    int imgH = cn.getTexture().getImgHeight();

    double y_ratio = intersection.getZ() >= 0 ?
            intersection.getZ() :
            (double)imgH - abs(intersection.getZ());
    y_ratio = fmin(mod(y_ratio, imgH) / imgH, 1);

    Vector v(0, 0, 0, intersection.getX(), intersection.getY(), 0);
    Vector x_axis(0, 1, 0);
    double alpha = v.angleWith(x_axis);
    alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
    double x_ratio = fmin(alpha / 360, 1);

    return cn.getTexture().getImageTextureAt(y_ratio, x_ratio);
}