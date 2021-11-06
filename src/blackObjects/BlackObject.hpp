#pragma once

#include "./../objects/components/Point.hpp"

class BlackObject
{
    public:
        BlackObject();
        virtual ~BlackObject();
        virtual bool contains(const Point &p) const = 0;
};