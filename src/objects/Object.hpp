#pragma once

#include <vector>
#include <iostream>
#include "components/Line.hpp"
#include "components/Point.hpp"
#include "components/Vector.hpp"
#include "./../color/Color.hpp"
#include "./../color/Texture.hpp"
#include "./../intersection/Intersection.hpp"

class Texture;
class Intersection;

class Object
{
    protected:
        std::vector<Color> colors;
        Texture texture;
        int reflexion;
        
    public:
        Object();
        Object(const Color &color);
        virtual ~Object();

        Color getColor() const;
        Color getColor(int i) const;
        Texture getTexture() const;
        int getReflexion() const;

        void addColor(const Color &color);
        void setTexture(const Texture &texture);
        void setReflexion(int r);

        virtual std::vector<Intersection> intersect(const Line &line) const = 0;
        virtual double angleWithAt(const Line &line, const Intersection &intersection) const = 0;
        virtual Line getReflectedRayAt(Intersection &intersection, const Line &line) const = 0;
        virtual Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};
