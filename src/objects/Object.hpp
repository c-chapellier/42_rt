#pragma once

#include <vector>
#include <iostream>
#include "components/Line.hpp"
#include "components/Point.hpp"
#include "./../color/Color.hpp"
#include "./../color/Texture.hpp"

class Object
{
    protected:
        std::vector<Color*> colors;
        Texture *texture;
    public:
        Object();
        Object(Color *color);
        virtual ~Object();

        virtual Point *intersect(const Line &line) const = 0;
        virtual double angleWith(const Line &line) const = 0;
        Color *getColor();
        Color *getColor(int i);
        Color *getColorAt(int height, int width, int screen_height, int screenWidth);
        void addColor(Color *color);
        void setTexture(Texture *texture);
};