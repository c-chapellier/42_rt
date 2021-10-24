#pragma once

#include <iostream>

#include "../header.hpp"
#include "../color/Color.hpp"

class Object;
class Point;

class Pixel
{
private:
    Color *color;
    double dist;    // distance between the camera and the viewed point
    Point *location_3d;
    Object *obj;

public:
    Pixel();
    Pixel(int red, int green, int blue, int opacity, double dist = INFINITY);
    Pixel(Color *c, double dist = INFINITY);
    ~Pixel();

    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    int getOpacity() const;
    Color *getColor();
    double get_dist() const;
    Point *get_location();
    Object *get_object();

    void setColor(const Color &color);
    void setLocation(Point *p);
    void setObject(Object *obj);
    void setDist(double dist);

    Pixel &operator=(const Pixel &pxl);
};