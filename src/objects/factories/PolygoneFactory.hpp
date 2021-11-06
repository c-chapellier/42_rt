#pragma once

#include "./../Polygone.hpp"
#include "./../transformer/Transformer.hpp"

class Polygone;

class PolygoneFactory
{
    private:
        PolygoneFactory();

        static Polygone *create1NEdron(const Point &p, int precision, double height, double r, double alpha, double beta, double gama, const Color &color);
        static Polygone *create2NEdron(const Point &p, int precision, double height, double r, double alpha, double beta, double gama, const Color &color);
        static Polygone *createParallelepiped(const Point &p, double height, double width, double length, double alpha, double beta, double gama, const Color &color);
        static Polygone *createDiamond(const Point &p, double h, double H, double r, double R, double alpha, double beta, double gama, const Color &color);
        static Polygone *createTape(const Point &p, double R, double width, int precision, double alpha, double beta, double gama, const Color &color);
        static Polygone *createClosedTape(const Point &p, double R, double width, int precision, double alpha, double beta, double gama, const Color &color);
        static Polygone *createMobiusTape(const Point &p, double R, double width, int precision, double alpha, double beta, double gama, const Color &color);
        static Polygone *createSpiral(const Point &p, double R, double width, int precision, int nb_turns, double alpha, double beta, double gama, const Color &color);
        static Polygone *createTower(const Point &p, double R, double width, int precision, int layers, double alpha, double beta, double gama, const Color &color);
        static Polygone *createTorus(const Point &p, double R, double r, int precision, int layers, double alpha, double beta, double gama, const Color &color);
        static Polygone *createRing(const Point &p, double R, double r, int precision, double alpha, double beta, double gama, const Color &color);
        static Polygone *createCircle(const Point &p, double R, int precision, double alpha, double beta, double gama, const Color &color);
        static Polygone *createStar(const Point &p, double R, double r, double thick, int branch, double alpha, double beta, double gama, const Color &color);
    public:
        static Polygone *createPolygone(const std::string &type, const Point &p, double size1, double size2, double size3, double size4, double alpha, double beta, double gama);
        static Polygone *createPolygone(const std::string &type, const Point &p, double size1, double size2, double size3, double size4, double alpha, double beta, double gama, const Color &color);
};