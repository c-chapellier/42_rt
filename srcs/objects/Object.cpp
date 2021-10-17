#include "Object.hpp"

Object::Object()
{
    this->color = new Color();
    this->colors.push_back(new Color());
    this->colors.push_back(new Color());
    this->colors.push_back(new Color());
}
Object::~Object()
{
    delete(this->color);
}

Color *Object::getColor()
{
    return this->color;
}

Color *Object::getColor(int i)
{
    if(i < 0 || i > (int)this->colors.size())
        throw "Bad index for accessing color of the object";
    return this->colors[i];
}