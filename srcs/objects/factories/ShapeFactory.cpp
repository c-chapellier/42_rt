#include "ShapeFactory.hpp"

ShapeFactory::ShapeFactory(){}

std::list<Object*> ShapeFactory::createShape(std::string type, Point &p, Color *color)
{
    if(type == "DNA") {
        return createDNA(p, color);
    }
    throw
        "Unrecognized type of shape";
}

std::list<Object*> ShapeFactory::createDNA(Point &p, Color *color) {
    std::list<Object*> objects;

    int height = 30;
    int width = 100;

    for (int i = 0; i < 15; ++i) {
        double alpha = i * (360 / 6);
        double beta = alpha + 180;
        Point p1(p.getX() + (width / 2) * cos(RADIAN(alpha)), p.getY() + (width / 2) * sin(RADIAN(alpha)), p.getZ() + (i * height));
        Point p2(p.getX() + (width / 2) * cos(RADIAN(beta)), p.getY() + (width / 2) * sin(RADIAN(beta)), p.getZ() + (i * height));
        objects.push_back(new Quadratic(p1, 1, 1, 1, 0, 0, 0, 0, 0, 0, -80, color));
        objects.push_back(new Quadratic(p2, 1, 1, 1, 0, 0, 0, 0, 0, 0, -80, color));
    }
    return objects;
}
