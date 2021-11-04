#pragma once

#include "BlackObject.hpp"
#include "./../objects/components/Point.hpp"

class BlackSphere : public BlackObject
{
    private:
        Point p;
        double r;
    public:
        BlackSphere(double x, double y, double z, double r);
        BlackSphere(Point &p, double r);
        ~BlackSphere();

        bool contains(Point &p);
};