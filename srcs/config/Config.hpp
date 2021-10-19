#pragma once

#include "./../header.hpp"

class Config
{
    private:
        int width;
        int height;
        int precision;
        Color *ambient_color;
        Color *blur;
    public:
        Config();
        ~Config();

        int getHeight();
        int getWidth();
        int getPrecision();
        Color *getAmbientColor();
        Color *getBlur();

        void setHeight(int h);
        void setWidth(int w);
        void setPrecision(int p);
        void setAmbientColor(int r, int g, int b, int o);
        void setBlur(int r, int g, int b, int o);
        
};