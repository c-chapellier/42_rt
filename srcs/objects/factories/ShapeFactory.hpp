#pragma once

#include <list>
#include "./../../header.hpp"

class ShapeFactory
{
    private:
        ShapeFactory();

        static std::list<Object*> createDNA(Point &p, Color *Color);
    public:
        static std::list<Object*> createShape(std::string type, Point &p, Color *color);
};