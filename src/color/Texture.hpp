#pragma once

#include <string>
#include <iostream>
#include <fstream>

class Texture
{
    private:
        std::string type;
        int value1;
        int value2;
        std::string file;
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
        std::string getFile() const;

        void setType(std::string type);
        void setValue1(int v1);
        void setValue2(int v2);
        void setFile(std::string file);
};