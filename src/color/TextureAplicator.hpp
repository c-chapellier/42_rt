#pragma once

#include "./../objects/Object.hpp"
#include "./../objects/Sphere.hpp"
#include "./../objects/Cylinder.hpp"

class Point;
class Object;
class Sphere;
class Cylinder;


class TextureAplicator
{
    private:
        
    public:
        static Color applyTexture(Object *o, Point &intersection);

        static Color applyTextureOnSphereAt(const Sphere &sp, const Point &intersection);
        static Color applyTextureOnCylinderAt(const Cylinder &cl, const Point &intersection);
};