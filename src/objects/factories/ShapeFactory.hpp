#pragma once

#include <vector>
#include "./../../header.hpp"

class ShapeFactory
{
    private:
        ShapeFactory();

        static std::vector<Object *> createDNA(const Point &p);
        static std::vector<Object *> createSphereCircle(const Point &p, double radius, int nb_sphere, double sphere_radius, double alpha, double beta, double gama);
    public:
        static std::vector<Object *> createShape(const std::string &type, const Point &p, double size1, double size2, double size3, double alpha, double beta, double gama);
};