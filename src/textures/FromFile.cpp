
#include "FromFile.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb/stb_image.h"

FromFile::FromFile(const std::string &filename)
{
    this->texture = stbi_load(filename.c_str(), &this->width, &this->height, &this->bpp, 3);
    if (this->texture == NULL) throw "texture filename not good";
}

FromFile::~FromFile()
{
    stbi_image_free(this->texture);
}

Vec3 FromFile::get_color(const hit_t &hit) const
{
    int i = (hit.u + 1) * this->height / 2;
    int j = (hit.v + 1) * this->width / 2;
    int n = (i * this->width + j) * this->bpp;

    return Vec3(
        (double)(this->texture[n]) / 255,
        (double)(this->texture[n + 1]) / 255,
        (double)(this->texture[n + 2]) / 255
    );
}