#pragma once

#include "./../objects/components/Point.hpp"

class BlackObject
{
    public:
        BlackObject();
        virtual ~BlackObject();
        virtual bool contains(Point &p) = 0;
};