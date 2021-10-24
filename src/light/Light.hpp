#pragma once

#include "../header.hpp"

class Light
{
private:
    Point *p;
    Color *color;

public:
    Light(double px, double py, double pz, Color *color);
    ~Light();

    Point *getP();
    Color *getColor();
};