#pragma once


#include "Object.hpp"
#include "./../solver/EquationSolver.hpp"
#include "../exceptions/NoInterException.hpp"

class Intersection;

class MobiusTape : public Object
{
    private:
        Point p;
        double A, B, C, D, E, F, G;

        Plane tangentAt(const Point &intersection) const;
    public:
        MobiusTape(double px, double py, double pz);
        MobiusTape(double px, double py, double pz, double A, double B, double C, double D, double E, double F, double G);
        ~MobiusTape();

        std::vector<Intersection> intersect(const Line &line) const;;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};