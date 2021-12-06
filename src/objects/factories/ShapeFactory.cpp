#include "ShapeFactory.hpp"

ShapeFactory::ShapeFactory(){}

std::vector<Object *> ShapeFactory::createShape(const std::string &type, const Point &p, double size1, double size2, double size3, double alpha, double beta, double gama)
{
    if (type == "DNA") {
        return createDNA(p);
    } else if(type == "SphereCircle") {
        return createSphereCircle(p, size1, size2, size3, alpha, beta, gama);
    }
    throw
        "Unrecognized type of shape";
}

std::vector<Object *> ShapeFactory::createDNA(const Point &p) {
    std::vector<Object *> objects;

    return objects;
}

std::vector<Object *> ShapeFactory::createSphereCircle(const Point &p, double radius, int nb_sphere, double sphere_radius, double alpha, double beta, double gama)
{
    std::vector<Object *> objects;

    for (int i = 0; i < nb_sphere; ++i) {
        // double angle = i * (360 / nb_sphere);
        // Point p1(radius * cos(RADIAN(angle)),radius * sin(RADIAN(angle)), 0);
        // Transformer::rotateAroundX(&p1, alpha);
        // Transformer::rotateAroundY(&p1, beta);
        // Transformer::rotateAroundZ(&p1, gama);
        // Transformer::translate(&p1, p);
        // objects.push_back(new Quadratic(p1, 1, 1, 1, 0, 0, 0, 0, 0, 0, -pow(sphere_radius, 2)));
    }
    return objects;
}