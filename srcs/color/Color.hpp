#pragma once

#include <stdlib.h>
#include <iostream>

class Color
{
    private:
        int r;
        int g;
        int b;
        int o;

        void generateRandomColor();
    public:
        Color();
        Color(int o);
        Color(int r, int g, int b);
        Color(int r, int g, int b, int o);
        ~Color();

        int getR();
        int getG();
        int getB();
        int getO();

        void setR(int r);
        void setG(int g);
        void setB(int b);
        void setO(int o);

        Color *reduceOf(double pourcentage);

        friend std::ostream& operator<<(std::ostream& out, const Color& color);
};