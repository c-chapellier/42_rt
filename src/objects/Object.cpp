#include "Object.hpp"

Object::Object()
    : texture()
{
    this->reflexion = 0;
}

Object::Object(const Color &color)
    : texture()
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

Color Object::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    screenWidth = intersection.getX();

    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        double p = (double)((double)height / (double)screen_height);
        return Color(
            this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * p),
            this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * p),
            this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * p),
            this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * p)
        );
    } else if (this->texture.getType() == "Grid") {
        return this->getColor(((height / this->texture.getValue1()) + (width / this->texture.getValue2())) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        return this->getColor((width / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        return this->getColor((height / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "Image") {
        throw "Texture type has no power here";
    } else {
        throw "Should never happen";
    }
}