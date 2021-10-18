#pragma once

#include <iostream>

#include "../header.hpp"
#include "../color/Color.hpp"

class Pixel
{
private:
    int red;
    int green;
    int blue;
    int opacity;
    double dist;    // distance between the camera and the viewed point

public:
    Pixel();
    Pixel(int red, int green, int blue, int opacity, double dist = INFINITY);
    Pixel(Color *c, double dist = INFINITY);
    ~Pixel();

    int get_red();
    int get_green();
    int get_blue();
    int get_opacity();
    double get_dist();

    Pixel &operator=(const Pixel &pxl);
};