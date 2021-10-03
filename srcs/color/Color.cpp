#include "Color.hpp"

Color::Color()
{
    this->generateRandomColor();
    this->o = 255;
}

Color::Color(int o)
{
    this->generateRandomColor();
    this->setO(o);
}
Color::Color(int r, int g, int b)
{
    this->setR(r);
    this->setG(g);
    this->setB(b);
    this->o = 255;
}
Color::Color(int r, int g, int b, int o)
{
    this->setR(r);
    this->setG(g);
    this->setB(b);
    this->setO(o);
}
Color::~Color()
{}

int Color::getR()
{
    return this->r;
}
int Color::getG()
{
    return this->g;
}
int Color::getB()
{
    return this->b;
}
int Color::getO()
{
    return this->o;
}

void Color::setR(int r)
{
    this->r = r < 0 ? (0) : (r > 255 ? (255): (r));
}
void Color::setG(int g)
{
    this->g = g < 0 ? (0) : (g > 255 ? (255): (g));
}
void Color::setB(int b)
{
    this->b = b < 0 ? (0) : (b > 255 ? (255): (b));
}
void Color::setO(int o)
{
    this->o = o < 0 ? (0) : (o > 255 ? (255): (o));
}

void Color::generateRandomColor()
{
    this->r = rand() % 256;
    this->g = rand() % 256;
    this->b = rand() % 256;
}

std::ostream& operator<< (std::ostream& out, const Color& color)
{
    out << "Color : {" << std::endl
    << "\tr: " << color.r << std::endl
    << "\tg: " << color.g << std::endl
    << "\tb: " << color.b << std::endl
    << "\to: " << color.o << std::endl
    << '}' << std::endl;
    return out;
}