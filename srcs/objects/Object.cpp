#include "Object.hpp"

Object::Object()
{
    this->texture = NULL;
}

Object::Object(Color *color)
{
    this->texture = NULL;
    if (color != NULL)
        this->colors.push_back(color);
}

Object::~Object(){
    delete(this->texture);
}

Color *Object::getColor()
{
    if(this->colors.size() == 0)
        throw "Bad index for accessing color of the object";
    return this->colors[0];
}

Color *Object::getColor(int i)
{
    if(i < 0 || i > (int)this->colors.size())
        throw "Bad index for accessing color of the object";
    return this->colors[i];
}

Color *Object::getColorAt(int height, int width, int screen_height, int screenWidth)
{
    screenWidth = 0;

    if (this->texture->getType() == "Uniform") {
        return getColor();
    } else if (this->texture->getType() == "Gradient") {
        double p = (double)((double)height / (double)screen_height);
        return new Color(
            getColor(0)->getR() + (int)((double)((double)getColor(1)->getR() - (double)getColor(0)->getR()) * p),
            getColor(0)->getG() + (int)((double)((double)getColor(1)->getG() - (double)getColor(0)->getG()) * p),
            getColor(0)->getB() + (int)((double)((double)getColor(1)->getB() - (double)getColor(0)->getB()) * p),
            getColor(0)->getO() + (int)((double)((double)getColor(1)->getO() - (double)getColor(0)->getO()) * p)
            // std::min(getColor(0)->getR(), getColor(1)->getR()) + (int)(((double)std::max(getColor(0)->getR(), getColor(1)->getR()) - std::min(getColor(0)->getR(), getColor(1)->getR())) * p),
            // std::min(getColor(0)->getG(), getColor(1)->getG()) + (int)(((double)std::max(getColor(0)->getG(), getColor(1)->getG()) - std::min(getColor(0)->getG(), getColor(1)->getG())) * p),
            // std::min(getColor(0)->getB(), getColor(1)->getB()) + (int)(((double)std::max(getColor(0)->getB(), getColor(1)->getB()) - std::min(getColor(0)->getB(), getColor(1)->getB())) * p),
            // std::min(getColor(0)->getO(), getColor(1)->getO()) + (int)(((double)std::max(getColor(0)->getO(), getColor(1)->getO()) - std::min(getColor(0)->getO(), getColor(1)->getO())) * p)
        );
    } else if (this->texture->getType() == "Grid") {
        return getColor(((height / texture->getValue1()) + (width / texture->getValue2())) % 2);
    } else if (this->texture->getType() == "VerticalLined") {
        return getColor((width / texture->getValue1()) % 2);
    } else if (this->texture->getType() == "HorizontalLined") {
        return getColor((height / texture->getValue1()) % 2);
    } else {
        throw "Should never happen";
    }
}

void Object::addColor(Color *color)
{
    if (color == NULL)
        throw "Object::addColor: color == NULL";
    this->colors.push_back(color);
}

void Object::setTexture(Texture *texture)
{
    this->texture = texture;
}