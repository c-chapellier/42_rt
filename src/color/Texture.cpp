#include "Texture.hpp"

Texture::Texture()
{
    setType("Uniform");
    setValue1(0);
    setValue2(0);
    setHOffset(0);
    setWOffset(0);
    setSpeed(1);
    setFile("NoFile");
    setOpacity(255);
    img = NULL;
}
Texture::Texture(std::string type)
{
    setType(type);
    setValue1(0);
    setValue2(0);
    setHOffset(0);
    setWOffset(0);
    setSpeed(1);
    setFile("NoFile");
    setOpacity(255);
    img = NULL;
}
Texture::Texture(std::string type, std::string file)
{
    setType(type);
    setValue1(0);
    setValue2(0);
    setHOffset(0);
    setWOffset(0);
    setSpeed(1);
    setFile(file);
    setOpacity(255);
}
Texture::Texture(std::string type, int value1)
{
    setType(type);
    setValue1(value1);
    setValue2(0);
    setHOffset(0);
    setWOffset(0);
    setSpeed(1);
    setFile("NoFile");
    setOpacity(255);
    img = NULL;
}
Texture::Texture(std::string type, int value1, int value2)
{
    setType(type);
    setValue1(value1);
    setValue2(value2);
    setHOffset(0);
    setWOffset(0);
    setSpeed(1);
    setFile("NoFile");
    setOpacity(255);
    img = NULL;
}
Texture::Texture(std::string type, int value1, int value2, std::string file)
{
    setType(type);
    setValue1(value1);
    setValue2(value2);
    setHOffset(0);
    setWOffset(0);
    setSpeed(1);
    setFile(file);
    setOpacity(255);
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
float Texture::getHOffset() const
{
    return this->h_offset;
}
float Texture::getWOffset() const
{
    return this->w_offset;
}
float Texture::getSpeed() const
{
    return this->speed;
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
void Texture::setHOffset(float h)
{
    this->h_offset = h;
}
void Texture::setWOffset(float w)
{
    this->w_offset = w;
}
void Texture::setSpeed(float s)
{
    if(speed < 0)
        throw "Texture speed can not be under 0";
    this->speed = s;
}
void Texture::setOpacity(int o)
{
    if(o < 0 || o > 255)
        throw "Texture opacity must be between 0 and 255";
    this->opacity = o;
}

// https://wiki.libsdl.org/SDL_PixelFormat
Color Texture::getImageTextureAt(double h, double w)
{
    int height = floor((double)img->h * mod(h + h_offset, 1.0));
    int width = floor((double)img->w * mod(w * speed + w_offset, 1.0));

    if (img->format->BytesPerPixel == 1) {
        Uint8 index = ((uint8_t*)img->pixels)[height * img->w + width];
        SDL_Color *color = &img->format->palette->colors[index];
        return Color(color->r, color->g, color->b, color->a);
    } else if (img->format->BytesPerPixel == 3) {
        int r = (int)((uint8_t*)img->pixels)[((height * img->w + width) * 3)];
        int g = (int)((uint8_t*)img->pixels)[((height * img->w + width) * 3) + 1];
        int b = (int)((uint8_t*)img->pixels)[((height * img->w + width) * 3) + 2];
        return Color(r, g, b, opacity);
    } else if (img->format->BytesPerPixel == 4) {
        Uint8 red, green, blue, alpha;
        Uint32 temp, pixel;
        pixel = *(Uint32*)&((uint8_t*)img->pixels)[(height * img->w + width) * 4];

        /* Get Red component */
        temp = pixel & img->format->Rmask;  /* Isolate red component */
        temp = temp >> img->format->Rshift; /* Shift it down to 8-bit */
        temp = temp << img->format->Rloss;  /* Expand to a full 8-bit number */
        red = (Uint8)temp;

        /* Get Green component */
        temp = pixel & img->format->Gmask;  /* Isolate green component */
        temp = temp >> img->format->Gshift; /* Shift it down to 8-bit */
        temp = temp << img->format->Gloss;  /* Expand to a full 8-bit number */
        green = (Uint8)temp;

        /* Get Blue component */
        temp = pixel & img->format->Bmask;  /* Isolate blue component */
        temp = temp >> img->format->Bshift; /* Shift it down to 8-bit */
        temp = temp << img->format->Bloss;  /* Expand to a full 8-bit number */
        blue = (Uint8)temp;

        /* Get Alpha component */
        temp = pixel & img->format->Amask;  /* Isolate alpha component */
        temp = temp >> img->format->Ashift; /* Shift it down to 8-bit */
        temp = temp << img->format->Aloss;  /* Expand to a full 8-bit number */
        alpha = (Uint8)temp;

        return Color(red, green, blue, alpha);
    }
    throw "this kind of texture can not be loaded";
}