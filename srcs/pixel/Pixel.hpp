#pragma once

#include <iostream>

#include "./../color/Color.hpp"

class Pixel
{
private:
    int red;
    int green;
    int blue;
    int opacity;

public:
    Pixel();
    Pixel(int red, int green, int blue, int opacity);
    Pixel(Color *c);
    ~Pixel();

    int get_red();
    int get_green();
    int get_blue();
    int get_opacity();

    Pixel &operator=(const Pixel &pxl);
};