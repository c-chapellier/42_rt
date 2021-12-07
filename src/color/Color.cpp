#include "Color.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Color::Color()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->o = 0;
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

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

unsigned char Color::getR() const
{
    return this->r;
}
unsigned char Color::getG() const
{
    return this->g;
}
unsigned char Color::getB() const
{
    return this->b;
}
unsigned char Color::getO() const
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
    return (double)this->o / 255;
}

/* * * * * * * * * * * * * * * * * * * * *

*                SETTER                  *

* * * * * * * * * * * * * * * * * * * * */

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

/* * * * * * * * * * * * * * * * * * * * *

*               MODIFIERS                *

* * * * * * * * * * * * * * * * * * * * */

Color Color::reduceOf(double ratio) const
{
    if (ratio < 0.0 || ratio > 1.0){
        std::cout << ratio << std::endl;
        throw "Color::reduceOf percentage bad";
    }

    double new_r, new_g, new_b;

    new_r = (double)this->r * (1.0 - ratio);
    new_g = (double)this->g * (1.0 - ratio);
    new_b = (double)this->b * (1.0 - ratio);

    return Color(new_r, new_g, new_b, o);
}

Color Color::add(const Color &c)
{
    int r_tmp = this->r + c.r;
    int g_tmp = this->g + c.g;
    int b_tmp = this->b + c.b;

    this->r = r_tmp > 255 ? 255 : r_tmp;
    this->g = g_tmp > 255 ? 255 : g_tmp;
    this->b = b_tmp > 255 ? 255 : b_tmp;

    return *this;
}

/* * * * * * * * * * * * * * * * * * * * *

*              OPERATORS                 *

* * * * * * * * * * * * * * * * * * * * */

Color &Color::operator=(const Color &p)
{
    this->r = p.r;
    this->g = p.g;
    this->b = p.b;
    this->o = p.o;
    return *this;
}

std::ostream& operator<< (std::ostream& out, const Color& color)
{
    out << "Color : {" << std::endl
    << "\tr: " << (int)color.r << std::endl
    << "\tg: " << (int)color.g << std::endl
    << "\tb: " << (int)color.b << std::endl
    << "\to: " << (int)color.o << std::endl
    << '}' << std::endl;
    return out;
}