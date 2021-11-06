#pragma once

#include "./../objects/Object.hpp"
#include "./../objects/Sphere.hpp"

class Sphere;
class Object;
class Point;

class TextureAplicator
{
    private:
        
    public:
        static Color applyTexture(Object *o, Point &intersection);

        static Color applyTextureOnSphereAt(const Sphere &sp, const Point &intersection);
};