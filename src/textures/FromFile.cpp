
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
    double u = hit.u, v = hit.v;

    if (u < -1 || u >= 1 || v < -1 || v >= 1)
        printf("uv not in range 1: %f %f %d%d%d%d\n", u, v, u < -1, u >= 1, v < -1, v >= 1);

    PRINT("u: " << u);
    PRINT("v: " << v);

    int i = (u + 1) * this->height / 2;
    i = i >= this->height ? this->height - 1 : i;
    i = i < 0 ? 0 : i;

    int j = (v + 1) * this->width / 2;
    j = j >= this->width ? this->width - 1 : j;
    j = j < 0 ? 0 : j;

    int n = (i * this->width + j) * this->bpp;

    return Vec3(
        (double)(this->texture[n]) / 255,
        (double)(this->texture[n + 1]) / 255,
        (double)(this->texture[n + 2]) / 255
    );
}