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
        char type;
        int value1;
        int value2;
        float h_offset = 0;
        float w_offset = 0;
        float speed = 1;
        std::string file;
        SDL_Surface *img;
        //char opacity;
    public:
        Texture();
        Texture(char type);
        Texture(char type, std::string file);
        Texture(char type, int value1);
        Texture(char type, int value1, int value2);
        Texture(char type, int value1, int value2, std::string file);
        ~Texture();

        char getType() const;
        int getValue1() const;
        int getValue2() const;
        float getHOffset() const;
        float getWOffset() const;
        float getSpeed() const;
        std::string getFile() const;

        void setType(char type);
        void setValue1(int v1);
        void setValue2(int v2);
        void setHOffset(float h);
        void setWOffset(float w);
        void setSpeed(float s);
        void setFile(std::string file);
        //void setOpacity(char o);

        int getImgHeight() const;
        int getImgWidth() const;

        Color getImageTextureAt(double h, double w);
};