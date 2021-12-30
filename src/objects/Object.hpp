#pragma once

#include <vector>
#include <iostream>
#include "components/Line.hpp"
#include "components/Point.hpp"
#include "components/Vector.hpp"
#include "components/Transform.hpp"
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
        Transform tr;
        char reflexion;
        
    public:
        Object();
        Object(const Color &color);
        virtual ~Object();

        // getter
        Color getColor() const;
        Color getColor(int i) const;
        Texture getTexture() const;
        char getReflexion() const;

        // modifier
        void addColor(const Color &color);
        void setTexture(const Texture &texture);
        void setReflexion(int r);

        void updateMatrix(
            double alpha, 
            double beta, 
            double gama, 
            double scaling_x, 
            double scaling_y, 
            double scaling_z,
            double translation_x,
            double translation_y,
            double translation_z
        );

        // pure methodes
        virtual void intersect(std::vector<Intersection> *intersections, const Line &line) const = 0;
        virtual double angleWithAt(const Line &line, const Intersection &intersection) const = 0;
        virtual Line getReflectedRayAt(const Intersection &intersection, const Line &line) const = 0;
        virtual Color getColorAt(const Point &intersection) const = 0;
};
