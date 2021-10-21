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
        std::string filter;
    public:
        Config();
        ~Config();

        int getHeight();
        int getWidth();
        int getPrecision();
        Color *getAmbientColor();
        Color *getBlur();
        std::string getFilter();

        void setHeight(int h);
        void setWidth(int w);
        void setPrecision(int p);
        void setAmbientColor(int r, int g, int b, int o);
        void setBlur(int r, int g, int b, int o);
        void setFilter(std::string filter);
        
};