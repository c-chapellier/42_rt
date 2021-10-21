#include "Config.hpp"

Config::Config()
{
    this->ambient_color = NULL;
    this->blur = NULL;
    setFilter("None");
}
Config::~Config()
{
    delete(this->ambient_color);
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
std::string Config::getFilter()
{
    return this->filter;
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
void Config::setAmbientColor(int r, int g, int b, int o)
{
    this->ambient_color = new Color(r, g, b, o);
}
void Config::setBlur(int r, int g, int b, int o)
{
    this->blur = new Color(r, g, b, o);
}
void Config::setFilter(std::string filter)
{
    if(filter != "None" && filter != "Sepia" && filter != "AverageGrayscale" && filter != "WeightedGrayscale" && filter != "Invert")
        throw "Unknown filter";
    this->filter = filter;
}