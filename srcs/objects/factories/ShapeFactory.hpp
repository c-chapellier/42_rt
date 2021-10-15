#pragma once

#include <list>
#include "./../../header.hpp"

class ShapeFactory
{
    private:
        ShapeFactory();

        static std::list<Object*> createDNA(Point &p);
    public:
        static std::list<Object*> createShape(std::string type, Point &p);
};