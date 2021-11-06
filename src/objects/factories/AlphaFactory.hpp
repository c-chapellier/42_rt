#pragma once

#include <vector>
#include "./../Polygone.hpp"

class Polygone;

class AlphaFactory
{
    private:
        AlphaFactory();

        static Polygone *createB(const Point &p, double height, double width, double thick, int offset);
        static Polygone *createI(const Point &p, double height, double width, double thick, int offset);
        static Polygone *createO(const Point &p, double height, double width, double thick, int offset);
        static Polygone *createU(const Point &p, double height, double width, double thick, int offset);
    public:
        static std::vector<Polygone *> createAlpha(const std::string &str, const Point &p, double height, double width, double thick);
};