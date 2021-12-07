#include "Object.hpp"

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

int Object::getReflexion() const
{
    return this->reflexion;
}

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

void Object::setAlpha(double alpha)
{
    tr.setAlpha(alpha);
}

void Object::setBeta(double beta)
{
    tr.setBeta(beta);
}

void Object::setGama(double gama)
{
    tr.setGama(gama);
}

void Object::setTranslation(double x, double y, double z)
{
    tr.setTranslation(x, y, z);
}

void Object::setScaling(double x, double y, double z)
{
    tr.setScaling(x, y, z);
}

void Object::updateMatrix()
{
    tr.updateMatrices();
}