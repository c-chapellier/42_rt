#pragma once

#include "./../header.hpp"

class Config
{
    private:
        int width;
        int height;
        Color *ambient_color;
    public:
        Config();
        ~Config();

        int getHeight();
        int getWidth();
        Color *getAmbientColor();

        void setHeight(int h);
        void setWidth(int w);
        void setAmbientColor(int r, int g, int b, int o);
        
};