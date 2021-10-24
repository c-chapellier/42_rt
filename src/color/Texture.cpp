#include "Texture.hpp"

Texture::Texture()
{
    setType("Uniform");
    setValue1(0);
    setValue2(0);
}
Texture::Texture(std::string type)
{
    setType(type);
    setValue1(0);
    setValue2(0);
}
Texture::Texture(std::string type, int value1)
{
    setType(type);
    setValue1(value1);
    setValue2(0);
}
Texture::Texture(std::string type, int value1, int value2)
{
    setType(type);
    setValue1(value1);
    setValue2(value2);
}
Texture::~Texture(){}

std::string Texture::getType()
{
    return this->type;
}
int Texture::getValue1()
{
    return this->value1;
}
int Texture::getValue2()
{
    return this->value2;
}

void Texture::setType(std::string type)
{
    if(
        type != "Uniform" && 
        type != "Gradient" && 
        type != "Grid" && 
        type != "VerticalLined" 
        && type != "HorizontalLined"
    )
        throw "Unknown type of texture";
    this->type = type;
}
void Texture::setValue1(int v1)
{
    if(v1 < 0)
        throw "Bad value of texture";
    this->value1 = v1;
}
void Texture::setValue2(int v2)
{
    if(v2 < 0)
        throw "Bad value of texture";
    this->value2 = v2;
}