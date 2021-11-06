#pragma once

#include "../header.hpp"

class Light
{
private:
    Point p;
    Color color;

public:
    Light(double px, double py, double pz, const Color &color);
    ~Light();

    Point getP() const;
    Color getColor() const;
};