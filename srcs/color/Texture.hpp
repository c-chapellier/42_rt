#pragma once

#include <string>

class Texture
{
    private:
        std::string type;
        int value1;
        int value2;
    public:
        Texture();
        Texture(std::string type);
        Texture(std::string type, int value1);
        Texture(std::string type, int value1, int value2);
        ~Texture();

        std::string getType();
        int getValue1();
        int getValue2();

        void setType(std::string type);
        void setValue1(int v1);
        void setValue2(int v2);
};