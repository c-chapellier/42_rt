#include "Object.hpp"

Object::Object()
{
    //this->colors.push_back(new Color());
}

Object::Object(Color *color)
{
    if(color != NULL)
        this->colors.push_back(color);
}

Object::~Object(){}

Color *Object::getColor()
{
    return this->colors[0];
}

Color *Object::getColor(int i)
{
    if(i < 0 || i > (int)this->colors.size())
        throw "Bad index for accessing color of the object";
    return this->colors[i];
}

void Object::addColor(Color *color)
{
    this->colors.push_back(color);
}