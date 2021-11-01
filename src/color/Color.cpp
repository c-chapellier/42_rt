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
Color::~Color(){}

int Color::getR() const
{
    return this->r;
}
int Color::getG() const
{
    return this->g;
}
int Color::getB() const
{
    return this->b;
}
int Color::getO() const
{
    return this->o;
}
double Color::getPR() const
{
    return (double)this->r / 255;
}
double Color::getPG() const
{
    return (double)this->g / 255;
}
double Color::getPB() const
{
    return (double)this->b / 255;
}
double Color::getP() const
{
    return (double)((double)this->o / (double)255);
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
int Color::getByO(int c)
{
    double p = (double)((double)this->o / (double)255);
    double res = (double)c * p;
    return (int)res;
}

Color Color::reduceOf(double ratio) const
{
    if (ratio < 0.0 || ratio > 1.0)
        throw "Color::reduceOf percentage bad";

    double new_r, new_g, new_b;

    new_r = (double)this->r * (1.0 - ratio);
    new_g = (double)this->g * (1.0 - ratio);
    new_b = (double)this->b * (1.0 - ratio);

    return Color((int)new_r, (int)new_b, (int)new_g, this->o);
}

Color Color::add(const Color &c)
{
    this->r += c.getR();
    this->g += c.getG();
    this->b += c.getB();

    if (this->r > 255)
        this->r = 255;   
    if (this->g > 255)
        this->g = 255;    
    if (this->b > 255)
        this->b = 255;
        
    return Color(this->r, this->g, this->b, this->o);
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