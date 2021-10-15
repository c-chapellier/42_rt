#pragma once

#include <iostream>
#include "components/Line.hpp"
#include "components/Point.hpp"
#include "./../color/Color.hpp"

class Object
{
    protected:
        Color *color;
    public:
        Object();
        Object(Color *color);
        virtual ~Object();
        virtual Point *intersect(Line *line) = 0;
        virtual double angleWith(Line *line) = 0;
        Color *getColor();
};