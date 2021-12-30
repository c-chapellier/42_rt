#pragma once


#include "Object.hpp"
#include "./../header.hpp"
#include "./../solver/EquationSolver.hpp"

class Intersection;

class MobiusTape : public Object
{
    private:
        double A, B, C, D, E, F, G;

        Plane tangentAt(const Point &intersection) const;
    public:
        MobiusTape(double A, double B, double C, double D, double E, double F, double G);
        ~MobiusTape();

        void intersect(std::vector<Intersection> *intersections, const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(const Intersection &intersection, const Line &line) const;
        Color getColorAt(const Point &intersection) const;
};