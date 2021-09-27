#pragma once

#include <iostream>
#include "Line.hpp"
#include "components/Point.hpp"

class Object
{
    private:

    public:
        virtual Point *intersect(Line line) = 0;
};