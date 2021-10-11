#include "Object.hpp"

Object::Object()
{
    this->color = new Color();
}
Object::~Object()
{
    delete(this->color);
}

Color *Object::getColor()
{
    return this->color;
}