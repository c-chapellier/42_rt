#pragma once

#include "./../header.hpp"

class Config
{
    private:
        int width;
        int height;
        int precision;
        Color ambient_color;
        int blur;
        std::string filter;
        bool perlinNoise;
        int maxReflexion;
    public:
        Config();
        ~Config();

        int getHeight() const;
        int getWidth() const;
        int getPrecision() const;
        Color getAmbientColor() const;
        int getBlur() const;
        std::string getFilter() const;
        bool getPerlinNoise() const;
        int getMaxReflection() const;

        void setHeight(int h);
        void setWidth(int w);
        void setPrecision(int p);
        void setAmbientColor(const Color &ambient);
        void setBlur(int b);
        void setFilter(const std::string &filter);
        void setPerlinNoise(bool perlinNoise);
        void setMaxReflection(int max);
};