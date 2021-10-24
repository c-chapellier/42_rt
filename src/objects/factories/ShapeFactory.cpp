#include "ShapeFactory.hpp"

ShapeFactory::ShapeFactory(){}

std::vector<Object*> ShapeFactory::createShape(std::string type, Point &p, double size1, double size2, double size3, double alpha, double beta, double gama)
{
    if(type == "DNA") {
        return createDNA(p);
    } else if(type == "SphereCircle") {
        return createSphereCircle(p, size1, size2, size3, alpha, beta, gama);
    }
    throw
        "Unrecognized type of shape";
}

std::vector<Object*> ShapeFactory::createDNA(Point &p) {
    std::vector<Object*> objects;

    int height = 30;
    int width = 100;

    for (int i = 0; i < 15; ++i) {
        double alpha = i * (360 / 6);
        double beta = alpha + 180;
        Point p1(p.getX() + (width / 2) * cos(RADIAN(alpha)), p.getY() + (width / 2) * sin(RADIAN(alpha)), p.getZ() + (i * height));
        Point p2(p.getX() + (width / 2) * cos(RADIAN(beta)), p.getY() + (width / 2) * sin(RADIAN(beta)), p.getZ() + (i * height));
        objects.push_back(new Quadratic(p1, 1, 1, 1, 0, 0, 0, 0, 0, 0, -80));
        objects.push_back(new Quadratic(p2, 1, 1, 1, 0, 0, 0, 0, 0, 0, -80));
    }
    return objects;
}

std::vector<Object*> ShapeFactory::createSphereCircle(Point &p, double radius, int nb_sphere, double sphere_radius, double alpha, double beta, double gama)
{
    std::vector<Object*> objects;

    for (int i = 0; i < nb_sphere; ++i) {
        double angle = i * (360 / nb_sphere);
        Point p1(radius * cos(RADIAN(angle)),radius * sin(RADIAN(angle)), 0);
        Transformer::rotateAroundX(&p1, alpha);
        Transformer::rotateAroundY(&p1, beta);
        Transformer::rotateAroundZ(&p1, gama);
        Transformer::translate(&p1, &p);
        objects.push_back(new Quadratic(p1, 1, 1, 1, 0, 0, 0, 0, 0, 0, -pow(sphere_radius, 2)));
    }
    return objects;
}