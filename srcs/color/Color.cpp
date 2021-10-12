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

Color *Color::reduceOf(double ratio)
{
    if (ratio < 0.0 || ratio > 1.0)
        throw "Color::reduceOf percentage bad";
    double new_r, new_g, new_b;
    new_r = (double)this->r * (1.0 - ratio);
    new_g = (double)this->g * (1.0 - ratio);
    new_b = (double)this->b * (1.0 - ratio);
    return new Color((int)new_r, (int)new_b, (int)new_g);
}

Color *Color::add(Color *c)
{
    this->r += c->getR();
    this->g += c->getG();
    this->b += c->getB();
    this->o += c->getO();

    if (this->r > 255)
        this->r = 255;   
    if (this->g > 255)
        this->g = 255;    
    if (this->b > 255)
        this->b = 255;
    if (this->o > 255)
        this->o = 255;
        
    return this;
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