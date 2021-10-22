#include "Config.hpp"

Config::Config()
{

}

Config::~Config()
{

}

int Config::getHeight()
{
    return this->height;
}
int Config::getWidth()
{
    return this->width;
}
int Config::getPrecision()
{
    return this->precision;
}
Color *Config::getAmbientColor()
{
    return this->ambient_color;
}
Color *Config::getBlur()
{
    return this->blur;
}

void Config::setHeight(int h)
{
    if(h <= 0)
        throw "Height can not be under or equal to 0";
    this->height = h;
}
void Config::setWidth(int w)
{
    if(w <= 0)
        throw "Width can not be under or equal to 0";
    this->width = w;
}
void Config::setPrecision(int p)
{
    if(p <= 0)
        throw "Width can not be under or equal to 0";
    this->precision = p;
}
void Config::setAmbientColor(Color *ambient)
{
    this->ambient_color = ambient;
}
void Config::setBlur(Color *blur)
{
    this->blur = blur;
}