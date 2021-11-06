#pragma once

#include "./../header.hpp"

class Config
{
    private:
        int width;
        int height;
        int precision;
        Color *ambient_color;
        int blur;
        std::string filter;
        bool perlinNoise;
    public:
        Config();
        ~Config();

        int getHeight() const;
        int getWidth() const;
        int getPrecision() const;
        Color *getAmbientColor();
        int getBlur() const;
        std::string getFilter();
        bool getPerlinNoise() const;

        void setHeight(int h);
        void setWidth(int w);
        void setPrecision(int p);
        void setAmbientColor(Color *ambient);
        void setBlur(int b);
        void setFilter(std::string filter);
        void setPerlinNoise(bool perlinNoise);
};