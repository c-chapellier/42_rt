#pragma once

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>

#include "Color.hpp"
#include "./../headers/define.hpp"

class Texture
{
    private:
        std::string type;
        int value1;
        int value2;
        float h_offset;
        float w_offset;
        float speed;
        std::string file;
        SDL_Surface *img;
    public:
        Texture();
        Texture(std::string type);
        Texture(std::string type, std::string file);
        Texture(std::string type, int value1);
        Texture(std::string type, int value1, int value2);
        Texture(std::string type, int value1, int value2, std::string file);
        ~Texture();

        std::string getType() const;
        int getValue1() const;
        int getValue2() const;
        float getHOffset() const;
        float getWOffset() const;
        float getSpeed() const;
        std::string getFile() const;

        void setType(std::string type);
        void setValue1(int v1);
        void setValue2(int v2);
        void setHOffset(float h);
        void setWOffset(float w);
        void setSpeed(float s);
        void setFile(std::string file);

        Color getImageTextureAt(double h, double w);
};