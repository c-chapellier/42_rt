#pragma once

#include <vector>
#include "./../Polygone.hpp"

class AlphaFactory
{
    private:
        AlphaFactory();

        static Polygone *createB(Point &p, double height, double width, double thick, int offset);
        static Polygone *createI(Point &p, double height, double width, double thick, int offset);
        static Polygone *createO(Point &p, double height, double width, double thick, int offset);
        static Polygone *createU(Point &p, double height, double width, double thick, int offset);
    public:
        static std::vector<Polygone *> createAlpha(std::string str, Point &p, double height, double width, double thick);
};