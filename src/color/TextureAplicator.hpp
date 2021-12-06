#pragma once

#include <math.h>

#include "./../objects/Object.hpp"
#include "./../objects/Sphere.hpp"
#include "./../objects/Cylinder.hpp"
#include "./../objects/Cone.hpp"
#include "./../objects/PlaneObj.hpp"

class Point;
class Object;
class Sphere;
class Cylinder;
class Cone;
class PlaneObj;


class TextureAplicator
{
    private:
        
    public:
        static Color applyTexture(Object *o, Point &intersection);

        static Color applyTextureOnSphereAt(const Sphere &sp, const Point &intersection);
        static Color applyTextureOnCylinderAt(const Cylinder &cl, const Point &intersection);
        static Color applyTextureOnConeAt(const Cone &cn, const Point &intersection);
        static Color applyTextureOnPlaneAt(const PlaneObj &pl, const Point &intersection);
};