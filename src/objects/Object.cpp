#include "Object.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Object::Object()
    : texture(), tr()
{
    this->reflexion = 0;
}

Object::Object(const Color &color)
    : texture(), tr()
{
    this->colors.push_back(color);
    this->reflexion = 0;
}

Object::~Object() {}

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

Color Object::getColor() const
{
    if (this->colors.size() == 0)
        throw "Bad index for accessing color of the object";
    return Color(this->colors[0]);
}

Color Object::getColor(int i) const
{
    if (i < 0 || i > (int)this->colors.size())
        throw "Bad index for accessing color of the object";
    return Color(this->colors[i]);
}

Texture Object::getTexture() const
{
    return this->texture;
}

char Object::getReflexion() const
{
    return this->reflexion;
}

/* * * * * * * * * * * * * * * * * * * * *

*                SETTER                  *

* * * * * * * * * * * * * * * * * * * * */

void Object::addColor(const Color &color)
{
    this->colors.push_back(color);
}

void Object::setTexture(const Texture &texture)
{
    this->texture = texture;
}

void Object::setReflexion(int r)
{
    if (r > 100 || r < 0)
        throw "Reflexion must be between 0 and 100";
    this->reflexion = r;
}

void Object::updateMatrix(
    double alpha, 
    double beta, 
    double gama, 
    double scaling_x, 
    double scaling_y, 
    double scaling_z,
    double translation_x,
    double translation_y,
    double translation_z
) {
    tr.updateMatrices(alpha, beta, gama, scaling_x, scaling_y, scaling_z, translation_x, translation_y, translation_z);
}