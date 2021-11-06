#include "Config.hpp"

Config::Config()
{
    this->ambient_color = NULL;
    this->blur = 0;
    setFilter("None");
}

Config::~Config()
{

}

int Config::getHeight() const
{
    return this->height;
}
int Config::getWidth() const
{
    return this->width;
}
int Config::getPrecision() const
{
    return this->precision;
}
Color *Config::getAmbientColor()
{
    return this->ambient_color;
}
int Config::getBlur() const
{
    return this->blur;
}
std::string Config::getFilter()
{
    return this->filter;
}
bool Config::getPerlinNoise() const
{
    return this->perlinNoise;
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

void Config::setBlur(int b)
{
    if(b < 0 || b > 10)
        throw "Blur must be between 0 and 10";
    this->blur = b;
}

void Config::setFilter(std::string filter)
{
    if(filter != "None" && filter != "Sepia" && filter != "AverageGrayscale" && filter != "WeightedGrayscale" && filter != "Invert")
        throw "Unknown filter";
    this->filter = filter;
}
void Config::setPerlinNoise(bool perlinNoise)
{
    this->perlinNoise = perlinNoise;
}