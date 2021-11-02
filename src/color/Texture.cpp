#include "Texture.hpp"

Texture::Texture()
{
    setType("Uniform");
    setValue1(0);
    setValue2(0);
    setFile("NoFile");
    img = NULL;
}
Texture::Texture(std::string type)
{
    setType(type);
    setValue1(0);
    setValue2(0);
    setFile("NoFile");
    img = NULL;
}
Texture::Texture(std::string type, std::string file)
{
    setType(type);
    setValue1(0);
    setValue2(0);
    setFile(file);
}
Texture::Texture(std::string type, int value1)
{
    setType(type);
    setValue1(value1);
    setValue2(0);
    setFile("NoFile");
    img = NULL;
}
Texture::Texture(std::string type, int value1, int value2)
{
    setType(type);
    setValue1(value1);
    setValue2(value2);
    setFile("NoFile");
    img = NULL;
}
Texture::Texture(std::string type, int value1, int value2, std::string file)
{
    setType(type);
    setValue1(value1);
    setValue2(value2);
    setFile(file);
}
Texture::~Texture(){}

std::string Texture::getType() const
{
    return this->type;
}

int Texture::getValue1() const
{
    return this->value1;
}

int Texture::getValue2() const
{
    return this->value2;
}

std::string Texture::getFile() const
{
    return this->file;
}

void Texture::setType(std::string type)
{
    if(
        type != "Uniform" && 
        type != "Gradient" && 
        type != "Grid" && 
        type != "VerticalLined" &&
        type != "HorizontalLined" &&
        type != "Image"
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
void Texture::setFile(std::string file)
{
    if(file == "NoFile")
        return ;
    this->img = IMG_Load(file.c_str());
    std::cout << file << std::endl;
    if (this->img == nullptr) {
        throw "IMG_Load: Failed to load required jpg and png support!";
    } 
    this->file = file;
}

Color Texture::getImageTextureAt(double h, double w)
{
    int height = floor((double)img->h * h);
    int width = floor((double)img->w * w);
    int r = (int)((uint8_t*)img->pixels)[((height * img->w + width) * 3)];
    int g = (int)((uint8_t*)img->pixels)[((height * img->w + width) * 3) + 1];
    int b = (int)((uint8_t*)img->pixels)[((height * img->w + width) * 3) + 2];
    return Color(r, g, b, 255);
}